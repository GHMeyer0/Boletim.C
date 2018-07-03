	
	string Disciplina::obterNome(string cod)
	{
		string n;
		registro.codigo = cod;
		if ( this->procurarCodigo() )
		{
			n = tabelaDisciplinas[posicao].nome;
		}
		else
		{
			n = "Nao encontrada";
		}
		return n;
	}
    void Disciplina::definirPonteiros(Nota *pn)
	{
		pontNotas = pn;
	}
	
	
	Disciplina::Disciplina()
	{
		this->lerArquivo();
	}
	
	

	// gerencia a logica do CRUD
	void Disciplina::executarCRUD()
	{
		Tela t;
		bool achou;
		string resp;
		
		
		
		this->montarTela();
		this->entrarCodigo();
		achou = this->procurarCodigo();
		
		if ( not achou )
		{
			resp = t.perguntar("Codigo nao encontrada. Deseja cadastrar novo aluno (S/N) : ",24);
			if (resp == "S")
			{
				this->entrarDados();
				resp = t.perguntar("Confirma cadastro (S/N) : ",24);
				if (resp == "S")
				{
					this->tabelaDisciplinas.push_back(this->registro);
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
					this->tabelaDisciplinas[this->posicao] = this->registro;
				}
			}
			
			if (resp=="E")
			{				
				if (this->tabelaDisciplinas[this->posicao].codigo == pontNotas->tabelaNotas[pontNotas->procurarCodigoMateria(registro.codigo)].codDisciplina)
				{
					t.perguntar("Existe notas lançadas para esta materia",24);
				}
				else
				{
					resp = t.perguntar("Confirma exclusao (S/N) : ",24);
					if(resp=="S")
					{
						this->tabelaDisciplinas.erase( this->tabelaDisciplinas.begin() + this->posicao );
					}
				}
			}
		}
		
		this->gravarArquivo();
	}


	void Disciplina::montarTela()
	{
		Tela t;
		t.montarMoldura(15,7,59,14,1);
		textcolor(YELLOW);
		gotoxy(16,8); cout << "Cadastro de Disciplina";
		textcolor(WHITE);
		gotoxy(16,10); cout << "Codigo    :";
		gotoxy(16,11); cout << "Nome      :";
		gotoxy(16,12); cout << "Carga Hor.:";
		gotoxy(16,13); cout << "Professor :";
	}
	
	
	void Disciplina::entrarCodigo()
	{
		Tela t;
		t.centralizar("Informe o codigo",24);
		gotoxy(28,10);
		getline(cin, registro.codigo);
	}
	
	
	bool Disciplina::procurarCodigo()
	{
		int x;
		bool achei = false;
		for (x=0; x<tabelaDisciplinas.size(); x++)
		{
			if (registro.codigo == tabelaDisciplinas[x].codigo)
			{
				achei = true;
				this->posicao = x;
				break;
			}
		}
		return achei;
	}
	
	
	void Disciplina::entrarDados()
	{
		Tela t;
		
		t.limparArea(28,11,58,13);
		
		t.centralizar("Informe o nome",24);
		gotoxy(28,11); getline(cin, registro.nome);
		
		t.centralizar("Informe a carga horaria",24);
		gotoxy(28,12); getline(cin, registro.carga);
		
		t.centralizar("Informe o professor",24);
		gotoxy(28,13); getline(cin, registro.professor);
	}
	
	
	void Disciplina::mostrarDados()
	{
		gotoxy(28,11); cout << this->tabelaDisciplinas[this->posicao].nome;
		gotoxy(28,12); cout << this->tabelaDisciplinas[this->posicao].carga;
		gotoxy(28,13); cout << this->tabelaDisciplinas[this->posicao].professor;
	}
	
	
	void Disciplina::lerArquivo()
	{
		ifstream arquivo;
		arquivo.open("disciplinas.txt");
		tabelaDisciplinas.clear();
		while ( not arquivo.eof() )   // end of file
		{
			getline(arquivo, registro.codigo, '|');
			getline(arquivo, registro.nome, '|');
			getline(arquivo, registro.carga, '|');
			getline(arquivo, registro.professor);
			
			if (registro.codigo != "")
			{
				tabelaDisciplinas.push_back(registro);
			}
		}
		arquivo.close();
	}
	
	
	void Disciplina::gravarArquivo()
	{
		ofstream arquivo;
		arquivo.open("disciplinas.dat");
		for (int i=0; i<tabelaDisciplinas.size(); i++)
		{
			arquivo << tabelaDisciplinas[i].codigo << "|";
			arquivo << tabelaDisciplinas[i].nome << "|";
			arquivo << tabelaDisciplinas[i].carga << "|";
			arquivo << tabelaDisciplinas[i].professor << endl;
		}
		arquivo.close();
	}

