// estrutura do registro de Aluno
struct regAluno
{
	string 	matricula;
	string 	nome;
	string 	email;
	string 	telefone;
	int		nr_nt;
};

// classe Aluno
class Aluno
{
public:
	void definirPonteiros(Nota *pn)
	{
		pontNotas = pn;
	}
    // retorna o nome de um aluno
	string obterNome(string cod)
	{
		string n;
		registro.matricula=cod;
		if ( this->procurarMatricula() )
		{
			n = tabelaAlunos[posicao].nome;
		}
		else
		{
			n = "Nao encontrado";
		}
		return n;
	}

	Aluno()
	{
			this->lerArquivo();
	}



	// gerencia a logica do CRUD
	void executarCRUD()
	{
		Tela t;
		bool achou;
		string resp;
		
	
		
		this->montarTela();
		this->entrarMatricula();
		achou = this->procurarMatricula();
		
		if ( not achou )
		{
			resp = t.perguntar("Matricula nao encontrada. Deseja cadastrar novo aluno (S/N) : ",24);
			if (resp == "S")
			{
				this->entrarDados();
				resp = t.perguntar("Confirma cadastro (S/N) : ",24);
				if (resp == "S")
				{
					this->tabelaAlunos.push_back(this->registro);
				}
			}
		}
		else // if (achou)
		{
			this->mostrarDados();
			resp = t.perguntar("Deseja Alterar/Excluir/Voltar (A/E/V) : ",24);
			
			if (resp=="A")
			{
				this->entrarDados();
				resp = t.perguntar("Confirma alteracao (S/N) : ",24);
				if (resp=="S")
				{
					this->tabelaAlunos[this->posicao] = this->registro;
				}
			}
			
			if (resp=="E")
			{	
				if (this->tabelaAlunos[this->posicao] == pontNotas->tabelaNotas[pontNotas->procurarMatricula(registro.matricula)].codAluno){
					resp = t.perguntar("Não é possivel apagar este aluno, pois exitem notas registradas para ele...",24);
				}
				else
				{
					resp = t.perguntar("Confirma exclusao (S/N) : ",24);
					if (resp=="S")
					{
						this->tabelaAlunos.erase( this->tabelaAlunos.begin() + this->posicao );
					}
				}

			}
		}
		
		this->gravarArquivo();
	}

  
private:	
	regAluno registro;
	vector<regAluno> tabelaAlunos;
	int posicao;
	Nota *pontNotas;


	// monta a tela de cadastro do aluno
	void montarTela()
	{
		Tela t;
		t.montarMoldura(15,7,59,14,1);
		textcolor(YELLOW);
		gotoxy(16,8); cout << "Cadastro de Aluno";
		textcolor(WHITE);
		gotoxy(16,10); cout << "Matricula :";
		gotoxy(16,11); cout << "Nome      :";
		gotoxy(16,12); cout << "Email     :";
		gotoxy(16,13); cout << "Telefone  :";
	}
	
	
	// faz a entrada da matricula do aluno
	void entrarMatricula()
	{
		Tela t;
		t.centralizar("Informe a matricula",24);
		gotoxy(28,10);
		getline(cin, registro.matricula);
	}
	
	
	// procura por uma matricula na tabelaAlunos
	bool procurarMatricula()
	{
		int x;
		bool achei = false;
		for (x=0; x<tabelaAlunos.size(); x++)
		{
			if (registro.matricula == tabelaAlunos[x].matricula)
			{
				achei = true;
				this->posicao = x;
				break;
			}
		}
		return achei;
	}
	
	
	// faz a entrada de dados do registro
	void entrarDados()
	{
		Tela t;
		
		t.limparArea(28,11,58,13);
		
		t.centralizar("Informe o nome",24);
		gotoxy(28,11); getline(cin, registro.nome);
		
		t.centralizar("Informe o email",24);
		gotoxy(28,12); getline(cin, registro.email);
		
		t.centralizar("Informe o telefone",24);
		gotoxy(28,13); getline(cin, registro.telefone);
	}
	
	
	// mostra os dados da matricula encontrada
	void mostrarDados()
	{
		gotoxy(28,11); cout << this->tabelaAlunos[this->posicao].nome;
		gotoxy(28,12); cout << this->tabelaAlunos[this->posicao].email;
		gotoxy(28,13); cout << this->tabelaAlunos[this->posicao].telefone;
	}
	
	
	// le os dados dos alunos de um arquivo texto
	void lerArquivo()
	{
		ifstream arquivo;
		arquivo.open("alunos.txt");
		tabelaAlunos.clear();
		while ( not arquivo.eof() )   // end of file
		{
			getline(arquivo, registro.matricula, '|');
			getline(arquivo, registro.nome, '|');
			getline(arquivo, registro.email, '|');
			getline(arquivo, registro.telefone);
			
			if (registro.matricula != "")
			{
				tabelaAlunos.push_back(registro);
			}
		}
		arquivo.close();
	}
	
	
	// grava os dados do vetor tabelaAlunos no arquivo texto
	void gravarArquivo()
	{
		ofstream arquivo;
		arquivo.open("alunos.dat");
		for (int i=0; i<tabelaAlunos.size(); i++)
		{
			arquivo << tabelaAlunos[i].matricula << "|";
			arquivo << tabelaAlunos[i].nome << "|";
			arquivo << tabelaAlunos[i].email << "|";
			arquivo << tabelaAlunos[i].telefone << endl;
		}
		arquivo.close();
	}
};
