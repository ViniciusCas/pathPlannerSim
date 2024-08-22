# pathPlannerSim
Ambiente de simulação para algoritmos de path planning (Planejador de rotas)

![Aplicativo de planejador de caminhos](assets/screen.jpeg?raw=true "pathPlannerSim")

Uso
---

Nesse software foi implementado um simulador de planejador de caminhos de forma inteligente,o algoritmo implementado para isso foi a busca em árvore a partir do Rapdly Exploring Random Tree (RRT).

Autor
-----

Software desenvolvido por Vinicius Casimiro para testes no time de futebol de robôs da Unesp - Bauru [Carrossel Caipira](https://github.com/carrossel-caipira)

Dependências do sistema
-----------------------

- [MAKE](https://www.gnu.org/software/make/)
- [SFML](https://www.sfml-dev.org/download.php)

Como configurar ambiente
------------------------

### Linux/Unix

Caso esteja num sistema Debian ou derivados basta ter certeza de que as dependências estão sendo satisfeitas:

```bash
sudo apt-get install libsfml-dev make
```

Depois deve-se compilar os códigos a partir do Makefile rodando no terminal:

```bash
make
```

Para executar o aplicativo, o comando abaixo deve ser executado

```bash
./pathfinding_app
```

ou 
```bash
make run
```

Como usar
---------

### Instruções básicas

Para usar o planejador de caminhos é necessário atribuir no mínimo dois pontos, que se referem ao ponto de partida e o ponto objetivo, para isso o botão esquerdo do mouse é utilizado para atribuir suas posições.
Em seguida, caso seja desejado colocar obstaculos para dificutar o caminho é necessário que o botão direito seja clicado, assim habilitando o posicionamento de um obstáculo, para que esse seja por fim colocado, o botão esquerdo do mouse deve ser pressionado. 
Para que haja remoção dos componentes citados, a tecla "E" deve ser pressionada, assim, habilitando o modo Eraser(Borracha), nesse modo, qualquer elemento no canvas que for clicado, será removido.

### Rodando o planejador de caminhos

Quando pelo menos os pontos de inicio e chegada forem atribuídos, e os algoritmos forem selecionados na parte de baixo da tela, o botão "Play" pode ser clicado e os caminhos serão gerados e mostrado com a cor do botão referente à aquele algoritmo na tela.
Na barra em cima do canvas, também serão mostrados, o número de iterações e tamanho do caminho gerado, para cada algoritmo ativo.

### Edição e adição

Inicialmente para adicionar outros algortimos os arquivos de código do algoritmo (.h e .cpp)  deve ser adicionado na pasta "/algorithms", esse código deve seguir as estruturas da classe abstrata Algoritthm, assim deve herdar dessa.
Para utilizar o algoritmo implementado, na main do código, uma instancia desse algoritmo deve ser adicionada ao objeto window, a partir do método Window::addAlgorithm(Algorithm* alg).

------
License: [MIT](LICENSE.md)