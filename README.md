
# UIN-Campus

Système de gestion académique de l'Université Islamique du Niger.

## Technologies

- C++23
- GCC (MSYS2 UCRT64)
- CMake
- Ninja
- GDB
- Clangd
- Clang-format
- Clang-tidy
- Git et GitHub

## Structure

- `include/` : fichiers d'en-tête publics
- `src/` : implémentation de la bibliothèque
- `app/` : application principale
- `tests/` : tests du projet

## Construction

Configuration Debug :

```powershell
cmake --preset debug
cmake --build --preset debug
```

Configuration Release :

```powershell
cmake --preset release
cmake --build --preset release
```

## Exécution

```powershell
.\build\debug\uin-campus.exe
```
