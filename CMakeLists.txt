# CMakeList.txt: Projekt CMake pro piskvorky, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (piskvorky "piskvorky.cpp" "piskvorky.h" "logic.cpp" "logic.h" "visual.cpp" "visual.h" "bot.cpp" "bot.h")

# TODO: V případě potřeby přidejte testy a cíle instalace.
