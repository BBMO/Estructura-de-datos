using namespace std;
class Persona{
        int ced;
        char nom[30];
    public:
        Persona() { ced=0; }
        Persona( char *n, int c ) { ced=c; strcpy(nom,n); }
        int get_clave(int flag=0) { return ced; }
        char *get_nom() { return nom; }
        void set_nom(char *n) { strcpy(nom,n); }
        void set_ced(char *n) { ced= atoi(n); }


		bool operator<(Persona &p){
            return (ced < p.get_clave())? true: false;
        }
        bool operator>(Persona &p){
            return (ced > p.get_clave())? true: false;
        }
        friend ostream & operator<<(ostream &os, Persona c){
			os<<" "<<c.ced<<"  "<<c.nom;
			return os;
		}
};

