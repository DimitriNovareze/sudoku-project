#ifndef DAMIERSUDOKU_H
#define DAMIERSUDOKU_H

#include <QObject>



class DamierSudoku : public QObject {

    Q_OBJECT
public:

    explicit DamierSudoku(QObject *parent = nullptr);

    Q_PROPERTY(QList<QList<QString>> values MEMBER valeurs NOTIFY valChanged)
    Q_PROPERTY(int lvl MEMBER level NOTIFY level_fix)
    Q_PROPERTY(QList<QList<QString>> couleurs MEMBER colors NOTIFY colorChanged)



    DamierSudoku &operator=(const DamierSudoku &other);

    int GetValeur(int i, int j);

    void Set(int i, int j, int valeur);

    void colorer_ligne(int i, int c);
    void colorer_colonne(int i, int c);
    void writeCSV(const int damier[9][9], const std::string& filename);
    Q_INVOKABLE bool finish();

    Q_INVOKABLE void colorer_voisins( int Carre,int Case);
    Q_INVOKABLE bool resolve();
    Q_INVOKABLE void init(int niveau);
    Q_INVOKABLE void addValue(int i, int j, int value);
    Q_INVOKABLE bool isValid();
    bool isValid_sans_color();
    Q_INVOKABLE void changeColor(int i, int j, const QString& color);
    Q_INVOKABLE void sauver();
    Q_INVOKABLE void fix_level(int i);

    int lire_grille(std::string level_grille);
    Q_INVOKABLE void set_grille(int i);




private:
    int damier[9][9];//Les dimensions du tableau sont fixes donc pas de programmation dynamique.
    void matriceToVectors(); //On en a besoin pour transformer notre matrice en liste accéssible pour QML

    QList<QList<QString>> colors;   // contient les couleurs de chaque case
    QList<QList<QString>> valeurs;  // contient les valeurs de chaque case sous forme de Qstring

    int level = 0;
    std::string grille;

signals:
    void valChanged();
    void level_fix();
    void colorChanged();

};



#endif // DAMIERJEU_H
