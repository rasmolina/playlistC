//Trabalho prático ESD - EAD1 - Roberto Augusto Silva Molina SC3012905
//Cadastro de músicas e playlists
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAMANHO 300

//Item 1 - Manter cadastro de uma coleção de músicas e artistas em listas encadeadas
typedef struct musica {
 int id;
 char titulo[200];
 int id_artista;
 int duracao; //em segundos
} musica;


typedef struct artista {
 int id;
 char nome[200];
 char genero[200];
} artista;

typedef struct musica_no {
 musica *musica;
 struct musica_no *prox;
} musica_no;

typedef struct artista_no {
 artista *artista;
 struct artista_no *prox;
} artista_no;

//lista circular de músicas de uma playlist
typedef struct playlist_no {
 musica *musica;
 int qtdd; //parâmetro extra para auxiliar as funções de manipulação de playlist
 struct playlist_no *prox;
} playlist_no;

//Item 8 - As playlists são cadastradas em uma lista simplesmente encadeada
typedef struct lplaylists_no {
 int id;
 char nome[200];
 playlist_no *musicas;
 struct lplaylists_no *prox;
} lplaylists_no;

//Crio a lista de músicas com uma cabeça apontando pra null
musica_no *criaListaMusicas(){
    musica_no *head;
    head = malloc(sizeof(musica_no));
    head->prox = NULL;
    return head; 
}

//Crio a lista de artistas com uma cabeça apontando pra null
artista_no *criaListaArtistas(){
    artista_no *head;
    head = malloc(sizeof(artista_no));
    head->prox = NULL;
    return head; 
}

//Crio a playlist com uma cabeça apontando pra null
playlist_no *criaPlaylist(){
    playlist_no *head;
    head = malloc(sizeof(playlist_no));
    head->prox = NULL;
    return head;
}

//Crio a lista de playlist com uma cabeça apontando pra null
lplaylists_no *cria_listaPlaylist(){
    lplaylists_no *head;
    head = malloc(sizeof(lplaylists_no));
    head->prox = NULL;
    return head;
}

//Item 2 - Cadastra novo artista e o insere na lista encadeada
void cadastrarNovoArtista(artista_no *ini, int *id, char nome[200], char genero[200]){
    artista *novoArtista;
    novoArtista = malloc(sizeof(artista));
    novoArtista->id = ++(*id);
    strcpy(novoArtista->nome, nome);
    strcpy(novoArtista->genero, genero);

    artista_no* novo;
    novo = malloc(sizeof(artista_no));
    novo->artista = novoArtista;
    novo->prox = ini->prox;
    ini->prox = novo;
}

//Item 3 - Cadastra nova música e a insere na lista encadeada
void cadastrarNovaMusica(musica_no *ini, int *id, char titulo[200], int id_artista, int duracao){
    musica *novaMusica;
    novaMusica = malloc(sizeof(musica));
    novaMusica->id = ++(*id); //incremento o id
    novaMusica->id_artista = id_artista;
    strcpy(novaMusica->titulo, titulo);
    novaMusica->duracao = duracao;

    musica_no* nova;
    nova = malloc(sizeof(musica_no));
    nova->musica = novaMusica;
    nova->prox = ini->prox;
    ini->prox = nova;
}

//Item 4 - Imprime todas as músicas
void imprimirMusicas(musica_no *ini, artista_no *iniA){
    musica_no *aux = ini;
    artista_no *auxA = iniA;
    char nomeArtista[200];
    int h, m, s;
    if(ini->prox == NULL)
        printf("\nSem musicas cadastradas!\n");
    else {
        printf("\n*** LISTA DE MUSICAS ***\n");
        for(musica_no *aux = ini->prox; aux!=NULL; aux=aux->prox) {
            for(artista_no *auxA = iniA->prox; auxA!=NULL; auxA=auxA->prox)
                if (aux->musica->id_artista == auxA->artista->id)
                    strcpy(nomeArtista, auxA->artista->nome);
            //Conversao da duracao no formato HH:MM:SS
   		    h = (aux->musica->duracao) / (60*60);
		    m = (aux->musica->duracao - (h*60*60)) / 60;
		    s = (aux->musica->duracao) % 60;
            printf("%d - %s (%s) - duracao: %02d:%02d:%02d\n",aux->musica->id,aux->musica->titulo,nomeArtista,h,m,s);
        }
    }
}

//Item 5 - Imprime todos os artistas
void imprimirArtistas(artista_no *ini){
    artista_no *aux = ini;
    if(ini->prox == NULL)
        printf("\nSem artistas cadastrados!\n");
    else {
        printf("\n*** LISTA DE ARTISTAS ***\n");
        for(artista_no *aux = ini->prox; aux!=NULL; aux=aux->prox)
            printf("%d - %s (%s)\n",aux->artista->id,aux->artista->nome,aux->artista->genero);
    }
}

//Item 6 - Imprime todas as músicas de um artista específico
void imprimirMusicaPorArtista(int id, musica_no* ini, artista_no *iniA){
    int h,m,s;
    musica_no *aux = ini;
    artista_no *auxA = iniA;
    char nomeArtista[200];
    for(artista_no *auxA = iniA->prox; auxA!=NULL; auxA=auxA->prox)
        if (id == auxA->artista->id)
            strcpy(nomeArtista, auxA->artista->nome);

    printf("\n*** LISTA DE MUSICAS - ARTISTA: %s ***\n",nomeArtista);
    for(musica_no *aux = ini->prox; aux!=NULL; aux=aux->prox) {
        h = (aux->musica->duracao) / (60*60);
		m = (aux->musica->duracao - (h*60*60)) / 60;
		s = (aux->musica->duracao) % 60;
        if(aux->musica->id_artista == id)
            printf("%d - %s (%02d:%02d:%02d)\n",aux->musica->id,aux->musica->titulo,h,m,s);
    }

}

//Item 7 - Criação de playlist
//7a - Seleciono as músicas pela id
void selecionarMusicas(musica_no *ini, lplaylists_no *ini_lista_playlist, int *id_playlist){
	int musicas_id[TAMANHO];
    int localizaMusica;
	char entrada;
	char temp[100];
	int i =0;
	int num = 0;
	musica_no *p;
	playlist_no *q;
	playlist_no *iniPlay;
	iniPlay = malloc(sizeof(playlist_no));
	iniPlay->prox = ini;
	iniPlay->musica = NULL;
    iniPlay->qtdd = 0;
	printf("\n\nSelecione as musicas desejadas pelo id: ");
	fflush(stdin);
	do{
        scanf("%c", &entrada); //lê caracter a caracter até encontrar o "enter", desprezando o espaço vazio
        temp[i] = entrada;
        localizaMusica = 0;
        if (temp[i] == ' ' || temp[i] == '\n'){
            temp[i] = NULL;
            musicas_id[num] = atoi(temp); //converte o caracter para inteiro
			p = malloc(sizeof(musica_no));
            p = ini->prox;
            localizaMusica = buscaMusica(ini,musicas_id[num]); //Verifico se a música selecionada está cadastrada
            if (localizaMusica == 0){
                printf("A musica de id %d nao existe!\n",musicas_id[num]);
                break;
            }

			while (p && p->musica->id != musicas_id[num]){
				p = p->prox;
			}
			q = malloc(sizeof(playlist_no));
			q->prox = iniPlay->prox;
			q->musica = p->musica;
			iniPlay->prox = q;
            iniPlay->qtdd++;
            num++;
            i = -1;
        }
        i++;
    } while (entrada != '\n');

    if (localizaMusica != 0 )    
	    criarListaPlaylist(iniPlay, ini_lista_playlist, id_playlist);
    else
        printf("Nao foi possivel criar a playlist!\n");
}

//7b - Crio a playlist com os ids digitados
void criarListaPlaylist(playlist_no *ini_playlist, lplaylists_no *ini, int *idPlaylist){
    lplaylists_no *novaPlaylist;
    (*idPlaylist) ++;
    novaPlaylist = malloc(sizeof(lplaylists_no));
	novaPlaylist->id = (*idPlaylist);
   	printf("Digite o nome desejado para a Playlist: ");
	fflush(stdin);
	gets(novaPlaylist->nome);
    novaPlaylist->musicas = ini_playlist;
    novaPlaylist->prox = ini->prox;
    ini->prox = novaPlaylist;
    printf("Playlist cadastrada com sucesso!\n");
}

//Imprime a lista de playlists
void imprimirNomePlaylists(lplaylists_no *ini_lista_playlist) {
    printf("*** PLAYLISTS ***\n");
    lplaylists_no *p;
	p = malloc(sizeof(lplaylists_no));
    p = ini_lista_playlist->prox;
    while(p) {
        printf("\nid: %d - %s", p->id, p->nome);
        p = p->prox;
    }
}

//Busca uma playlist pelo id
lplaylists_no buscarPlaylist(lplaylists_no *ini_lista_playlist){
	int idEntrada;
	printf("\n\nDigite o id da playlist desejada: ");
	scanf("%d", &idEntrada);
	lplaylists_no *p;
	p = malloc(sizeof(lplaylists_no));
	p = ini_lista_playlist->prox;
	while(p && p->id != idEntrada){
		p = p->prox;
	}
	return *p;
}

//Item 10 - Imprime as músicas da playlist selecionada
void imprimirMusicasPlaylist(lplaylists_no *p){
	playlist_no *q;
	q = malloc(sizeof(playlist_no));
	q = p->musicas->prox;
    printf("*** Playlist: %s ***\n",p->nome);
	while(q->musica != NULL){
		printf("\nid - %d \t%s",q->musica->id ,q->musica->titulo);
		q = q->prox;
	}
}

//Item 9 - Função shuffle
//Primeiro gero um número aleatório e uma posição para troca para a playlist recebida
void function_shuffle(lplaylists_no *p){
	int i;
	int pos;
	int num;
	srand(time(NULL));
	for(i = 0; i < p->musicas->qtdd; i++){
		num = 1 + (rand() % ((p->musicas->qtdd)-1));
		trocarMusicas(num,i,p);
	}
    printf("\nModo shuffle ativado com sucesso!\n");
}

//Em seguida troco a posição de forma randômica com os parâmetros gerados
void trocarMusicas(int randomico, int indice, lplaylists_no *ini){
	int i;
	playlist_no *aux;
	aux = malloc(sizeof(playlist_no));
	playlist_no *dados;
	dados = malloc(sizeof(playlist_no));
	playlist_no *p;
	p = malloc(sizeof(playlist_no));
	playlist_no *q;
	q = malloc(sizeof(playlist_no));
	int cont;
	cont = ini->musicas->qtdd;
	//primeira musica playlist
	dados = ini->musicas->prox;
	for(i = 0; i < cont; i ++){
		if(i == randomico){
			p = dados;
		}
		if(i == indice){
			q = dados;
		}
		dados = dados->prox;
	}
	aux->musica = p->musica;
	p->musica = q->musica;
	q->musica = aux->musica;
}

//Item 11 - apagar música
//Primeiro removo a música de todas as playlists em que ela se encontra
void excluirMusicaPlaylist(int id, lplaylists_no *ini){
	// Busca em todas as playlists a musica procurada e a "exclui".
	playlist_no *anterior;
	lplaylists_no *playlist;
	playlist_no *musicaProcurada;
	playlist_no *musicaEncontrada;
	musicaProcurada = malloc(sizeof(playlist_no));
	playlist = ini->prox;
	while(playlist){
		musicaProcurada = playlist->musicas->prox;
		anterior = playlist->musicas;
		while(musicaProcurada->musica){
			if(musicaProcurada->musica->id == id){
				(playlist->musicas->qtdd)--;
				musicaEncontrada = musicaProcurada;
				anterior->prox = musicaProcurada->prox;
			}
			anterior = musicaProcurada;
			musicaProcurada = musicaProcurada->prox;
		}
		playlist = playlist->prox;
	}
}

//Em seguida eu removo a música da lista encadeada
musica_no* apagarMusica(musica_no *lista, int id){
    musica_no *aux, *remover = NULL;
    if(lista){
        aux = lista;
        while(aux->prox && aux->prox->musica->id != id)
            aux = aux->prox;
        if(aux->prox){
            remover = aux->prox;
            aux->prox = remover->prox;
        }
    }
    return remover;
}

//Item 12 - Apagar artista
//Primeiro eu apago todas as músicas do artista
musica_no* excluirMusicaArtista(musica_no *lista, int id){
	//Faço uma busca na lista de músicas: se a musica for do artista desejado ela é apagada
    musica_no *aux, *remover = NULL;
    while(lista != NULL){
        aux = lista;
        while(aux->prox && aux->prox->musica->id_artista != id)
            aux = aux->prox;
        if(aux->prox){
            remover = aux->prox;
            aux->prox = remover->prox;
        }
        lista = lista->prox;
    }
    return remover;
}

//Em seguida eu removo o artista
artista_no* apagarArtista(artista_no *lista, int id){
    artista_no *aux, *remover = NULL;
    if(lista){
        aux = lista;
        while(aux->prox && aux->prox->artista->id != id)
            aux = aux->prox;
        if(aux->prox){
            remover = aux->prox;
            aux->prox = remover->prox;
        }
    }
    return remover;
}

//Apago as músicas do artistas das playlists em que ele se encontrar
void excluirMusicaArtistaPlaylist(int id, lplaylists_no *ini){
	// Busca em todas as playlists a musica procurada e a "exclui".
	playlist_no *anterior;
	lplaylists_no *playlist;
	playlist_no *musicaProcurada;
	playlist_no *musicaEncontrada;
	musicaProcurada = malloc(sizeof(playlist_no));
	playlist = ini->prox;
	while(playlist){
		musicaProcurada = playlist->musicas->prox;
		anterior = playlist->musicas;
		while(musicaProcurada->musica){
			if(musicaProcurada->musica->id_artista == id){
				(playlist->musicas->qtdd)--;
				musicaEncontrada = musicaProcurada;
				anterior->prox = musicaProcurada->prox;
			}
			anterior = musicaProcurada;
			musicaProcurada = musicaProcurada->prox;
		}
		playlist = playlist->prox;
	}
}


int buscaArtista(artista_no *lista, int id){
    artista_no *aux = NULL;
    if(lista){
        aux = lista;
        while(aux->prox && aux->prox->artista->id != id)
            aux = aux->prox;
        if(aux->prox)
            return 1;
    }
}

int buscaMusica(musica_no *lista, int id){
    musica_no *aux = NULL;
    if(lista){
        aux = lista;
        while(aux->prox && aux->prox->musica->id != id)
            aux = aux->prox;
        if(aux->prox)
            return 1;
    }
}

//----------------------------------MENUS----------------------------------------
int menuPrincipal() {
	int op;
	printf("\n---------------------------------------------\n"
			"          SPOTIFSPY - MENU PRINCIPAL             "
			"\n---------------------------------------------\n"
			"1 - Menu musica\n"
	        "2 - Menu artista\n"
			"3 - Menu playlist\n"
			"4 - Sair\n\n"
			"Escolha uma opcao: ");
	fflush(stdin);
	scanf("%d", &op);
	return op;
}

int menuMusica() {
	int op;
	printf("\n---------------------------------------------\n"
			"               MENU MUSICA"
			"\n---------------------------------------------\n"
			"1 - Inserir musica\n"
			"2 - Excluir musica\n"
			"3 - Imprimir musicas\n"
	        "4 - Imprimir musicas por artista\n"
			"5 - Voltar\n\n"
			"Escolha uma opcao: ");
	scanf("%d", &op);
	return op;
}

int menuArtista() {
	int op;
	printf("\n---------------------------------------------\n"
			"               MENU ARTISTA"
			"\n---------------------------------------------\n"
			"1 - Inserir artista\n"
			"2 - Excluir artista\n"
			"3 - Imprimir artistas\n"
			"4 - Voltar\n\n"
			"Escolha uma opcao: ");
	scanf("%d", &op);
	return op;
}

int menuPlaylist() {
	int op;
	printf("\n\n---------------------------------------------\n"
			"               MENU PLAYLIST"
			"\n---------------------------------------------\n"
			"1 - Criar playlist\n"
			"2 - Imprimir playlists\n"
			"3 - Shuffle\n"
			"4 - Voltar\n\n"
			"Escolha uma opcao: ");
	scanf("%d", &op);
	return op;
}
//---------------------------------------------------------------------------------------

int main(){
    setlocale(LC_ALL, "Portuguese");
  	int op = 0;
    int lastidArtista = 0;
    int lastidMusica = 0;
    int lastidPlaylist = 0;
    artista_no *listaArtistas, *removidoArtista;
    musica_no *listaMusicas, *removidoMusica;
   	playlist_no *ini_playlist;
	lplaylists_no *ini_lista_playlist;
    lplaylists_no p;
    ini_playlist = criaPlaylist();
    ini_lista_playlist = cria_listaPlaylist();
    listaMusicas = criaListaMusicas();
    listaArtistas = criaListaArtistas();

    //Banco de dados para teste----------------------------------------------------------
    cadastrarNovoArtista(listaArtistas, &lastidArtista, "Caetano Veloso", "MPB");
    cadastrarNovoArtista(listaArtistas, &lastidArtista, "Alcione", "Samba");
    cadastrarNovoArtista(listaArtistas, &lastidArtista, "Chico Buarque", "MPB");
    cadastrarNovaMusica(listaMusicas, &lastidMusica, "O Leaozinho", 1, 200);
    cadastrarNovaMusica(listaMusicas, &lastidMusica, "Voce e linda", 1, 220);
    cadastrarNovaMusica(listaMusicas, &lastidMusica, "Evidencias", 2, 130);
    cadastrarNovaMusica(listaMusicas, &lastidMusica, "Nao deixe o samba morrer", 2, 230);
    cadastrarNovaMusica(listaMusicas, &lastidMusica, "A Banda", 3, 114);
    cadastrarNovaMusica(listaMusicas, &lastidMusica, "Roda Viva", 3, 230);    
    //-----------------------------------------------------------------------------------

	while (op != 4) {
		int op = menuPrincipal();
        int idArtista, idMusica, duracao;
        char genero[200], nomeArtista[200];
		//MENU MÚSICA
        char nomeMusica[200];
        if (op == 1) {
			int opcao = 0;
            int busca = 0;
			while (opcao != 5) {
				opcao = menuMusica();
				if (opcao == 1) {
                    printf("\nDigite o nome da musica: ");
                    fflush(stdin);
                    gets(nomeMusica);
                    printf("\nDigite a duracao da musica: ");
                    scanf("%d",&duracao);
                    imprimirArtistas(listaArtistas);
                    printf("\nDigite o id do Artista: ");
                    scanf("%d",&idArtista);
                    busca = buscaArtista(listaArtistas, idArtista); //verifico se existe o artista escolhido
                    if (busca != 0){
                        cadastrarNovaMusica(listaMusicas, &lastidMusica, nomeMusica, idArtista, duracao);
                        printf("\nMusica cadastrada com sucesso!\n");
                    } else{
                        printf("\nId de artista nao localizado!\n");
                        break;
                    }
				} else 
				if (opcao == 2) {
					if(listaMusicas->prox == NULL){
						printf("Nao existem musicas para serem excluidas!\n");
					}else{
						imprimirMusicas(listaMusicas, listaArtistas);
                        printf("\nQual musica deseja excluir? (digite o id): ");
						scanf("%d", &idMusica);
                        excluirMusicaPlaylist(idMusica,ini_lista_playlist); //apago a música das playlists
                        removidoMusica = apagarMusica(listaMusicas, idMusica); //apago a música
                        if (removidoMusica){
                            free(removidoMusica);
                            printf("\nMusica removida com sucesso!\n");
                        }else printf("\nMusica nao encontrada!\n");
					}
				}if (opcao == 3) {
					if(listaMusicas->prox == NULL){
						printf("Nao existem musicas para serem exibidas!\n");
					}else{
						imprimirMusicas(listaMusicas, listaArtistas);
					}
				}else
                if (opcao == 4){
                    busca = 0;
					if(listaMusicas->prox == NULL){
						printf("Nao existem musicas para serem exibidas!\n");
					}else{
						imprimirArtistas(listaArtistas);
                        printf("\nDigite o id do artista desejado: ");
                        scanf("%d",&idArtista);
                        busca = buscaArtista(listaArtistas, idArtista); //verifico se existe o artista escolhido
                        if (busca != 0)
                            imprimirMusicaPorArtista(idArtista,listaMusicas,listaArtistas);
                        else
                            printf("\nArtista nao encontrado!\n"); 
                        
					}
                }
			}
		} else 
		
		//MENU ARTISTA
        if (op == 2) {
			int opcao = 0;
			while (opcao != 4) {
				opcao = menuArtista();
				if (opcao == 1) {
		            printf("\nDigite o nome do artista: ");
                    fflush(stdin);
                    gets(nomeArtista);
		            printf("\nDigite o genero (estilo) do artista: ");
                    fflush(stdin);
                    gets(genero);
                    cadastrarNovoArtista(listaArtistas, &lastidArtista, nomeArtista, genero);
                    printf("\nArtista cadastrado com sucesso!\n");
        		}else if (opcao == 2) {
					if(listaArtistas->prox == NULL){
						printf("Nao existem artistas cadastrados\n");
					}else{
                        imprimirArtistas(listaArtistas);
                        printf("\nQual artista deseja excluir? (digite o id): ");
						scanf("%d", &idArtista);
                        removidoArtista = apagarArtista(listaArtistas, idArtista); //apago artista
                        if (removidoArtista){
                            free(removidoArtista);
                            removidoMusica = excluirMusicaArtista(listaMusicas,idArtista); //apago as músicas do artista
                            if (removidoMusica){
                                free(removidoMusica);
                                excluirMusicaArtistaPlaylist(idArtista, ini_lista_playlist); //apago as músicas desse artista das playlists em que ele se encontrar
                            }                            
                            else 
                                printf("Nao existem musicas deste artista para remover!");
                            printf("\nArtista removido com sucesso!\n");
                        }
                        else printf("\nArtista nao localizado!\n"); 						
					}
				} else if(opcao == 3){
					if(listaArtistas->prox == NULL){
						printf("\nNao existem artistas cadastrados!\n");
					}else imprimirArtistas(listaArtistas);
				}
			}
		} else 
        
        //MENU PLAYLIST
            if (op == 3) {
			int opcao = 0;
			while (opcao != 4) {
				opcao = menuPlaylist();
				if (opcao == 1) {
                    imprimirMusicas(listaMusicas, listaArtistas);
                    selecionarMusicas(listaMusicas, ini_lista_playlist, &lastidPlaylist);
				}else 
                if (opcao == 2) {
                        if (ini_lista_playlist->prox != NULL) {
                            imprimirNomePlaylists(ini_lista_playlist);
                            p = buscarPlaylist(ini_lista_playlist);
                            imprimirMusicasPlaylist(&p); //Imprime playlist
                        }else printf("\nNao existem playlists cadastradas!\n");
				} else 
                if(opcao == 3){
                    if (ini_lista_playlist->prox != NULL){
                        imprimirNomePlaylists(ini_lista_playlist);
                        p = buscarPlaylist(ini_lista_playlist); //seleciona a playlist desejada
                        imprimirMusicasPlaylist(&p); //Imprime as músicas da playlist escolhida
                        function_shuffle(&p); //Ativa o shuffle
                        imprimirMusicasPlaylist(&p); //imprime as músicas da playlist após o shuffle
                    }else printf("\nNao existem playlists cadastradas!\n");
				}
			}
		}
		else {
			break;
        }
		
	}
    getchar();  
}