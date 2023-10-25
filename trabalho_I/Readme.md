## TRABALHO DE ESTRUTURAS DE DADOS II PARA A PRIMEIRA AVALIAÇÃO
### 1) (3,0 pontos) Faça um programa em C que cadastre as seguintes árvores:
    (a) Séries: código, título, número de temporadas, um endereço para uma árvore binária de busca contendo
    informações de cada temporada. A árvore deve ser organizada pelo código da série.

    (b) Temporadas: número da temporada, título, quantidade de episódios, ano, endereço para ula lista simples
    de participantes. A árvore de Temporadas deve ser organizada pelo número da temporada. Para a lista
    simples de participantes deve ter: nome artista, nome personagem e uma descrição sobre o personagem.
    A lista simples de participantes deve está em ordem alfabética do nome do artista

    Além de conter os cadastros no menu de opções, o mesmo de conter uma opção para cada item a seguir:
    (a) Imprimir em ordem pelo código da série: o título, o número de temporadas.
    (b) Imprimir os dados de todas as temporadas de uma série, cujo o usuário informe o código da série.
    (c) Imprimir todos os personagens de uma determinada temporada de uma dada série, cujo o usuário
    informe o código da série e o número da temporada.
    (d) Imprimir o nome de todos os artistas que interpretaram um determinado personagem em todas as
    temporadas de uma dada série, cujo o usuário informe o código da série.

### 2) (2,0 pontos) Em relação ao exercício 1, verifique os tempos:
    (a) de inserção de cada elemento na árvore de séries (no item a do exercício 1);

    (b) de busca de uma determinada temporada na árvore de temporada (no item b do exercício 1);

    Para verificar os tempos de execução pesquise pela função time do C. Insira no código comandos para obter
    o tempo inicial antes de fazer a pesquisa e o tempo final depois de concluir a pesquisa.

    Obs. 1: para os experimentos cada execução deve inserir os mesmos códigos de séries em ordem diferente
    (pode utilizar comando para embaralhar os códigos e assim as árvores ficarem bem aleatórias e
    poder verificar a diferença entre inserções).

    Obs. 2: Lembre-se que não pode haver impressão entre o tempo inicial e o tempo final, pois impressão
    consome muito tempo.

    Obs. 3: Para validar o tempo de busca, o mesmo deve ser repetido 30 vezes. Faça uma média para obter o
    resultado final.

### 3) (5,0 pontos) Repita todo o processo dos exercícios 1 e 2 mas agora implemente o código usando uma Árvore AVL.