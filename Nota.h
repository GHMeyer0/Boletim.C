struct regNota
{
	string codAluno;
	string codDisciplina;
	string sequencia;
	string nota;
};


class Nota
{
public:
	regNota registro;
	vector<regNota> tabelaNotas;
	int posicao;
	Nota(){
		
	}

	void definirPonteiros(Aluno *pa, Disciplina *pd)
	{
		pontAlunos = pa;
		pontDisciplinas = pd;
	}
	
	
	void emitirBoletim()
	{		
	}
	
	

	// gerencia a logica do CRUD
	void executarCRUD()
	{
		Tela t;
		bool achou;
		string resp;
		
		this->lerArquivo();
		
		this->montarTela();
		this->entrarCodigos();
		achou = this->procurarCodigos();
		
		if ( not achou )
		{	
			
			if (stoi(registro.sequencia)<=3) 
			{
				resp = t.perguntar("Registro nao encontrado. Deseja cadastrar nota (S/N) : ",24);
				if (resp == "S")
				{
					this->entrarDados();
					resp = t.perguntar("Confirma cadastro (S/N) : ",24);
					if (resp == "S")
					{
						this->tabelaNotas.push_back(this->registro);
					}
				}
			}
			
			else
			{
				t.perguntar("N�o � possivel registrar mais de 3 notas por aluno!!",24);
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
					this->tabelaNotas[this->posicao] = this->registro;
				}
			}
			
			if (resp=="E")
			{
				resp = t.perguntar("Confirma exclusao (S/N) : ",24);
				if (resp=="S")
				{
					this->tabelaNotas.erase( this->tabelaNotas.begin() + this->posicao );
				}
			}
		}
		
		this->gravarArquivo();
	}

	int procurarMatricula(string matricula){
		int i;
		
		for(i = 0; i < tabelaNotas.size(); i++)
		{	
			if (matricula == tabelaNotas[i].codAluno ) 
			{
				return i;
			}
			else
			{
				return tabelaNotas.size()+1;
			}
		}
	}
	int procurarCodigoMateria(string CodMat){
		int i;
		for(i = 0; i < tabelaNotas.size(); i++)
		{	
			if (CodMat == tabelaNotas[i].codAluno ) 
			{
				return i;
			}
			else
			{
				return tabelaNotas.size()+1;
			}
			
		}
	}	
private:	
	
	Aluno *pontAlunos; 
	Disciplina *pontDisciplinas;
	string n;

	bool procurarCodigos()
	{
		int x;
		bool achei = false;
		for (x=0; x<tabelaNotas.size(); x++)
		{
			if (registro.codAluno == tabelaNotas[x].codAluno &&
			    registro.codDisciplina == tabelaNotas[x].codDisciplina &&
			    registro.sequencia == tabelaNotas[x].sequencia)
			{
				achei = true;
				this->posicao = x;
				break;
			}
		}
		return achei;
	}

	void montarTela(int qual=1)
	{
		Tela t;
		if (qual==1)
		{
			t.montarMoldura(15,7,59,14,1);
			textcolor(YELLOW);
			gotoxy(16,8); cout << "Cadastro de Notas";
			textcolor(WHITE);
			gotoxy(16,10); cout << "Aluno      :";
			gotoxy(16,11); cout << "Disciplina :";
			gotoxy(16,12); cout << "Sequencia  :";
			gotoxy(16,13); cout << "Nota       :";
		}
		else if (qual == 2)
		{
			t.montarMoldura(15,7,59,12,1);
			textcolor(YELLOW);
			gotoxy(16,8); cout << "Emissao de Boletim";
			textcolor(WHITE);
		}
		else if (qual == 3){
			gotoxy(10,12); cout << "+---------------------------------------------------------------------------------+";
			gotoxy(10,13); cout << "|                                Boletim                                          |";
			gotoxy(10,14); cout << "|---------------------------------------------------------------------------------|";
			gotoxy(10,15); cout << "|  Disciplina          |  Nota 1  |  Nota 2  |  Nota 3  |  Media  | Situação      |";
			gotoxy(10,16); cout << "|---------------------------------------------------------------------------------|";
			gotoxy(10,17); cout << "|                      |          |          |          |         |               |";
			gotoxy(10,18); cout << "|---------------------------------------------------------------------------------|";
		}
	}
	
	
	vector<string> entrarTipo()
	{
		vector<string> config(2);
		gotoxy(16,11); cout << "Codigo do Aluno        :";
		gotoxy(41,11); getline(cin, config[1]);
		return config;
	}
	

	void entrarCodigos()
	{
		Tela t;
		t.centralizar("Informe o codigo do aluno",24);
		gotoxy(29,10); getline(cin, registro.codAluno);
		gotoxy(33,10); cout << pontAlunos->obterNome(registro.codAluno);

		t.centralizar("Informe o codigo da disciplina",24);
		gotoxy(29,11); getline(cin, registro.codDisciplina);
		gotoxy(33,11); cout << pontDisciplinas->obterNome(registro.codDisciplina);

		t.centralizar("Informe a sequencia da nota",24);
		gotoxy(29,12); getline(cin, registro.sequencia);
	}
	
	void entrarDados()
	{
		Tela t;
		
		t.limparArea(28,13,58,13);
		
		t.centralizar("Informe a nota",24);
		gotoxy(29,13); getline(cin, registro.nota);
	}
	
	
	void mostrarDados()
	{
		gotoxy(29,13); cout << this->tabelaNotas[this->posicao].nota;
	}
	
	
	void lerArquivo()
	{
		ifstream arquivo;
		arquivo.open("notas.txt");
		tabelaNotas.clear();
		while ( not arquivo.eof() )   // end of file
		{
			getline(arquivo, registro.codAluno, '|');
			getline(arquivo, registro.codDisciplina, '|');
			getline(arquivo, registro.sequencia, '|');
			getline(arquivo, registro.nota);
			if (registro.codAluno != "")
			{
				tabelaNotas.push_back(registro);
			}
		}
		arquivo.close();
	}
	
	
	void gravarArquivo()
	{
		ofstream arquivo;
		arquivo.open("notas.txt");
		for (int i=0; i<tabelaNotas.size(); i++)
		{
			arquivo << tabelaNotas[i].codAluno << "|";
			arquivo << tabelaNotas[i].codDisciplina << "|";
			arquivo << tabelaNotas[i].sequencia << "|";
			arquivo << tabelaNotas[i].nota << endl;
		}
		arquivo.close();
	}
};
