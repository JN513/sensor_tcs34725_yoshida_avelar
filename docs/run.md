# Execução do projeto

## Build

Para compilar o projeto, utilize:

```bash
mkdir -p src/build
cd src/build
cmake ..
make -j$(nproc)
```

## Load

Para carregar o firmware na placa BitDogLab, utilize o Picotool:

Caso você ainda esteja na pasta `src/build`, utilize:

```bash
picotool load main.uf2 -f
```

Caso você esteja na raiz do projeto, utilize:

```bash
picotool load src/build/main.uf2 -f
```