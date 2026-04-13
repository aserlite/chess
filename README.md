# Chess

# Compilation

Sur macOS, il faut bien penser à installer clang-tidy (par exemple en installant llvm) pour pouvoir compiler.
Avec brew, on peut installer llvm avec cette commande.
```bash
brew install llvm
```
> [!TIP]
> Clang-tidy sert juste à avoir des warnings supplémentaires quand on dev (éviter les anti-patterns, les fonctionnalités c++ dépréciées, etc.). Si on veut pas s'embêter avec llvm, il est aussi possible de commenter la ligne clang-tidy dans le fichier `CMakeLists.txt`.