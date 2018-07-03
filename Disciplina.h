struct regDisciplina
{
	string codigo;
	string nome;
	string carga;
	string professor;
};
class Disciplina
{
public:
	// retorna o nome da disciplina
	string obterNome(string cod);
	Disciplina();
	~Disciplina();
	void executarCRUD(Nota *pn);
private:	
	regDisciplina registro;
	vector<regDisciplina> tabelaDisciplinas;
	int posicao;
	Nota *pontNotas;

	void montarTela();
	void entrarCodigo();
	bool procurarCodigo();
	void entrarDados();
	void mostrarDados();
	void lerArquivo();
	void gravarArquivo();
};
