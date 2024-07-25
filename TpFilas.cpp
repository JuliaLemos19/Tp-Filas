#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

struct Guiche {
    int id;
    std::queue<int> senhasAtendidas;
};


void mostrarMenu() {
    std::cout << "\nMenu de Atendimento:\n";
    std::cout << "0. Sair\n";
    std::cout << "1. Gerar senha\n";
    std::cout << "2. Abrir guichê\n";
    std::cout << "3. Realizar atendimento\n";
    std::cout << "4. Listar senhas atendidas\n";
    std::cout << "Escolha uma opção: ";
}

int main() {
    std::queue<int> senhasGeradas; 
    std::unordered_map<int, Guiche> guiches; int proximaSenha = 1; 
    int totalSenhasAtendidas = 0; 

    int opcao = -1;
    
   
    while (opcao != 0 || !senhasGeradas.empty()) {
        mostrarMenu();
        std::cin >> opcao;

        switch (opcao) {
            case 0:
                if (!senhasGeradas.empty()) {
                    std::cout << "Ainda existem senhas aguardando atendimento. Não é possível encerrar o programa.\n";
                } else {
                    std::cout << "Programa encerrado. Total de senhas atendidas: " << totalSenhasAtendidas << std::endl;
                }
                break;

            case 1: {
                
                senhasGeradas.push(proximaSenha++);
                std::cout << "Senha " << proximaSenha - 1 << " gerada.\n";
                break;
            }

            case 2: {
                
                int idGuiche;
                std::cout << "Digite o ID do novo guichê: ";
                std::cin >> idGuiche;

                if (guiches.find(idGuiche) == guiches.end()) {
                    Guiche novoGuiche;
                    novoGuiche.id = idGuiche;
                    guiches[idGuiche] = novoGuiche;
                    std::cout << "Guichê " << idGuiche << " aberto.\n";
                } else {
                    std::cout << "Guichê " << idGuiche << " já está aberto.\n";
                }
                break;
            }

            case 3: {
               
                if (senhasGeradas.empty()) {
                    std::cout << "Nenhuma senha aguardando atendimento.\n";
                } else {
                    int idGuiche;
                    std::cout << "Digite o ID do guichê que está chamando: ";
                    std::cin >> idGuiche;

                    if (guiches.find(idGuiche) != guiches.end()) {
                        int senhaAtual = senhasGeradas.front();
                        senhasGeradas.pop();
                        guiches[idGuiche].senhasAtendidas.push(senhaAtual);
                        totalSenhasAtendidas++;
                        std::cout << "Senha " << senhaAtual << " atendida pelo guichê " << idGuiche << ".\n";
                    } else {
                        std::cout << "Guichê " << idGuiche << " não encontrado.\n";
                    }
                }
                break;
            }

            case 4: {
                
                int idGuiche;
                std::cout << "Digite o ID do guichê para listar senhas atendidas: ";
                std::cin >> idGuiche;

                if (guiches.find(idGuiche) != guiches.end()) {
                    std::queue<int> &senhasAtendidas = guiches[idGuiche].senhasAtendidas;
                    if (senhasAtendidas.empty()) {
                        std::cout << "Nenhuma senha atendida pelo guichê " << idGuiche << ".\n";
                    } else {
                        std::cout << "Senhas atendidas pelo guichê " << idGuiche << ": ";
                        while (!senhasAtendidas.empty()) {
                            std::cout << senhasAtendidas.front() << " ";
                            senhasAtendidas.pop();
                        }
                        std::cout << std::endl;
                    }
                } else {
                    std::cout << "Guichê " << idGuiche << " não encontrado.\n";
                }
                break;
            }

            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }


        std::cout << "Senhas aguardando: " << senhasGeradas.size() << std::endl;
        std::cout << "Guichês abertos: " << guiches.size() << std::endl;
    }

    return 0;
}
