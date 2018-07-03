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
	Aluno();
	//~Aluno();
	void definirPonteiros(Nota *pn);
    // retorna o nome de um aluno
	string obterNome(string cod);
	// gerencia a logica do CRUD
	void executarCRUD();  
private:	
	regAluno registro;
	vector<regAluno> tabelaAlunos;
	int posicao;
	Nota *pontNotas;
	// monta a tela de cadastro do aluno
	void montarTela();	
	// faz a entrada da matricula do aluno
	void entrarMatricula();		
	// procura por uma matricula na tabelaAlunos
	bool procurarMatricula();	
	// faz a entrada de dados do registro
	void entrarDados();
	// mostra os dados da matricula encontrada
	void mostrarDados();	
	// le os dados dos alunos de um arquivo texto
	void lerArquivo();
	// grava os dados do vetor tabelaAlunos no arquivo texto
	void gravarArquivo();
};
