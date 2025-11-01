# Dokumentace k semestrální práci - Hra housenka

**Autor:** Josef Talač
**Verze:** == pridat hash commitu == 

## 1. Popis herní logiky

### Herní smyčka
Hra využívá více vláken pro zajištění plynulého běhu. Hlavní logika je rozdělena do tří samostatných vláken:

1.  **Vstupní vlákno (`inputThread`):** Naslouchá vstup od uživatele (stisknutí klávesy) a bez blokování ostatních vláken, aktualizuje směr pohybu hada, připadně ukončení hry uživatelem.
2.  **Výpočetní vlákno (`computeThread`):** Zodpovídá za veškerou herní logiku – pohyb hada, detekci kolizí, sbírání předmětů a aktualizaci skóre. Mezi jednotlivými kroky smičky je vlákno uspáno, což určuje rychlost hry.
3.  **Vykreslovací vlákno (`renderThread`):** Stará se o vykreslení aktuálního stavu hry na terminál.

Synchronizace mezi vlákny je řešena pomocí `std::mutex` a `std::condition_variable`. Výpočetní vlákno po každé aktualizaci stavu "probudí" vykreslovací vlákno, aby zobrazilo změny. Mutex v programu zajišťuje to, že v jeden okamžik přistupuje ke sdíleným datům (stav hry, pozice hada ...) pouze jedno vlákno, čímž se předchází problémům se synchronizací.

### Pohyb hada
Had se pohybuje po krocích ve směru určeném vektorem pohybu (`x_vec`, `y_vec`). Při každé aktualizaci stavu hry, se hlava posune o jeden krok daným směrem. Tělo hada (ocas) se aktualizuje tak, že každý segment ocasu se posune na předchozí pozici segmentu před ním. Při sebrání předmětu se délka hada zvětší o jeden segment.

### Detekce kolizí
Při každém kroku herní logiky se kontrolují následující kolize:
*   **Kolize s okraji hracího pole:** Porovnávají se souřadnice hlavy hada s rozměry herního pole.
*   **Kolize se zdmi:** Kontroluje se, zda souřadnice hlavy hada není stejná jako souřadnice nějaké zdi.
*   **Kolize s vlastním tělem:** Zjišťuje se, zda se souřadnice hlavy hada nenachází v seznamu souřadnic ocasu.

V případě jakékoliv této kolize hra končí a zobrazí se skóre.

### Dynamická obtížnost
Rychlost hry se dynamicky mění v závislosti na zvolené obtížnosti a aktuálním skóre hráče.
*   **Rychlost:** S rostoucím skóre se zkracuje prodleva mezi kroky herní smyčky, čímž se hra zrychluje. Míra zrychlení a počáteční rychlost závisí na počáteční zvolené obtížnosti.
*   **Počet zdí:** Počet zdí je vypočten z velikosi herního pole a zvolené obtížnosti.

## 2. Popis tříd a metod

*   **`Game`**: Centrální třída řídící samotnou hru.
    *   `startGame()`: Spustí herní vlákna (input, compute, render).
    *   `stopGame()`: Ukončí herní vlákna a zobrazí obrazovku s koncem hry.
    *   `inputLoop()`, `computeLoop()`, `renderLoop()`: Metody implementující logiku pro jednotlivá vlákna hry.
    *   `updateSnake()`: Aktualizuje pozici hada na mapě.
    *   `checkCollisions()`: Kontroluje zda nedošlo ke kolizi hada s nějakým objektem na mapě, nebo s okrajem mapy.
    *   `inputHandle(char)`: Zpracovává vstup od uživatele a mění směr hada.
    *   `calculateGameSpeed()`: Vypočítá aktuální rychlost hry na základě skóre a obtížnosti.
    *   `renderGame()`: Vykreslí herní pole, hada, předměty a skóre.
    *   `endScreen()`: Zobrazí konečnout obrazovku s finálním skore hry.

*   **`GameMenu`**: Třída pro správu hlavního menu a nastavení hry, stará se o běh hry.
    *   `gameLoop()`: Hlavní smyčka menu, která zobrazí menu a reaguje na volby uživatele.
    *   `showMenu()`, `showSettings()`, `showControls()`: Metody pro zobrazení jednotlivých obrazovek (hlavní menu, nastavení, ovládání).
    *   `startGame()`: Vytvoří instanci `Game` a spustí hru s aktuálně nastavenými parametry.

*   **`Snake`**: Reprezentace hada.
    *   `Konstruktor` - umožňuje nastavit vychozi pozici hada, jeho delku a symboy ktere se budou vykreslovat za hlavu a tělo.
    *   `updateHead()`: Posune hlavu hada v aktuálním směru (určeným vektory).
    *   `updateTail()`: Aktualizuje segmenty ocasu.
    *   `incrementSize()`: Zvětší délku hada o jeden segment.
    *   `setDirection(string)`: Změní směr pohybu hada.
    *   `getTailCoords()`: Vrátí seznam pozic kde se nachází jednotlivé segmenty ocasu.

*   **`Item`**: Rodičovská třída pro všechny objekty na herní ploše. Uchovává jejich pozici (`x`, `y`) a grafický symbol.
    *   `respawnItem(width, height)`: Umístí předmět na náhodnou pozici v rámci herního pole.

*   **`CollectItem`**: Třída pro sběratelný předmět hadem, dědí z `Item`.

*   **`Walls`**: Třída spravující zdi v herním poli.
    *   `placeWalls(...)`: Náhodně rozmístí zdi po herní ploše, přičemž dává pozor, aby se zeď neobjevila v blízkém okolí hlavy hada. Zdi jsou reprezentovány jako pole objektů typu `Item`

*   **`FilePrinter`**: Pomocná statická třída.
*   `printFile(filePath, shouldAnimate)`: Vytiskne obsah souboru do konzole. Pokud je parametr shouldAnimate true, tak se po každém vytisknutém řádku chvíli počká (pro efekt animace).

## 3. Popis postupu kompilace a spuštění

### Požadavky
*   C++ překladač s podporou standardu C++20.
*   CMake (verze 4.0 nebo vyšší).

### Postup kompilace - cmake (linux)
1.  V kořenovém adresáři projektu vytvořte složku `build`:
    ```bash
    mkdir build
    ```
2.  Přejděte do nově vytvořené složky:
    ```bash
    cd build
    ```
3.  Spusťte CMake pro vygenerování buildovacích souborů:
    ```bash
    cmake ..
    ```
4.  Zkompilujte projekt:
    ```bash
    cmake --build .
    ```

### Spuštění hry
Po úspěšné kompilaci se ve složce `build` vytvoří spustitelný soubor `snejks`.

*   Spuštění hry s hlavním menu:
    ```bash
    ./snejks
    ```
*   Spuštění hry přímo (přeskočení menu):
    ```bash
    ./snejks --play
    ```
*   Zobrazení nápovědy:
    ```bash
    ./snejks --help
    ```

### Spuštění testů
Testy se kompilují spolu s hrou. Spustit je lze ze složky `build`:
```bash
ctest
```
nebo přímo:
```bash
./game-test-runner
```

## 4. Popis přepínačů (argumentů) programu

Program podporuje následující argumenty příkazové řádky:

*   `--help`, `-h`: Zobrazí nápovědu s popisem argumentů a ukončí program.
*   `--play`, `-p`: Spustí hru okamžitě s výchozím nastavením a přeskočí hlavní menu, po skončení hry se program ukončí.

## 5. Popis ovládání aplikace

Ovládání hry probíhá pomocí klávesnice:

| Klávesa | Akce                  |
|---------|-----------------------|
| `W`     | Pohyb nahoru (↑)      |
| `A`     | Pohyb doleva (←)      |
| `S`     | Pohyb dolů (↓)        |
| `D`     | Pohyb doprava (→)     |
| `T`     | Okamžité ukončení hry |

V menu se pro výběr možností používají číselné klávesy (`1`-`4`).

## 6. Testování programu

Program je testován pomocí jednotkových testů (unit tests) s využitím frameworku Catch2.

### Jednotkové testy
Sada testů (`game_tests/game_test.cpp`) pokrývá klíčové části logiky:
*   **`Snake constructor test`**: Ověřuje správné nastavení hodnot hada v konstruktoru.
*   **`Snake move test`**: Testuje pohyb hlavy hada a změnu směru.
*   **`Snake tail move test`**: Kontroluje, zda ocas správně následuje hlavu.
*   **`Item test spawn`**: Ověřuje, že se předměty objevují v platných souřadnicích.
*   **`Game difficulty affects wall count`**: Testuje, zda se počet zdí mění v závislosti na obtížnosti.
*   **`Game speed calculation`**: Ověřuje správnost výpočtu rychlosti hry na základě skóre.
*   **`GameMenu settings management`**: Kontroluje výchozí hodnoty nastavení v menu.
*   **`GameMenu settings modification`**: Testuje, zda je možné měnit nastavení hry (rozměry, obtížnost).

### Herní strategie

*   **Strategie pro výhru:**
    - hru není možné vyhrát, cílem je přežit co nejdéle a sesbírat co nejvíce předmětů 
*   **Prohra**:
    - hráč prohraje pokud narazí do okrajů mapy, do svého ocasu nebo do zdí na mapě


### Obrázky hry
![alt menu_image](image.png)
![alt text](image-2.png)