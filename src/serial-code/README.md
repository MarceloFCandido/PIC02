# Código serial

## Como executar?

### Parâmetros de entrada
Primeiramente, é necessário compilar o executável que criará os dados de
entrada: o `cli.exe`. Para tal, execute nessa pasta:
```
make cli-terminal
```
Após isso, "rode" o executável gerado com 
```
./cli.exe
```
e responder os as suas perguntas. Você também pode usar um dos exemplos da pasta
`data/inputs` passando à linha de comando
```
./cli.exe < data/inputs/example.in
```
substituindo `example` pelo nome de um dos arquivos da pasta. Você também pode
criar seus próprios exemplos respondendo às perguntas do `cli.exe` e copiando a
exibição das entradas que você realizou que ele fará ao fim das perguntas.

### O modelo de velocidades
Para simular a propagação de ondas, o programa precisa de um modelo de
velocidades. Para tal, basta compilar o código `gen-velocities-model.cpp` com 
```
make velocities
```
e depois executar 
```
./velocities.exe
```

### Realização dos cálculos
O passo seguinte é a realização dos cálculos da propagação de ondas. Para tal,
você precisará compilar o código calculador `main-reflect-bound.cpp` com
```
make mainly
```
e executá-lo com
```
./main.exe
```

### Exibição dos traços e *snapshots*
Para exibir os traços gerados, execute
```
python tracer.py
```
e, semelhantemente, para *snapshots*
```
python snapshoter.py
```
lembrando que os snapshots só serão gerados se assim for definido na entrada dos
parâmetros da seção 1.
