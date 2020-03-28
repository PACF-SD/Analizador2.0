#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <string>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    int stateMat [18][33]=
     //	L   l   d   E   e   +   -   *   /   %   >   <   =   !   &   |   (   )   [   ]   {   }   '   "   ;   .   :   ,   _  /B  /t  /n	~
    {{  2,  1,  3,  2,  1,107,108,109,110, 11, 11, 12, 10, 13, 14, 15,123,122,126,127,124,125, 16,  9,128,129,130,131,508,  0,  0,  0,500},
     {  2,  1,  2,  2,  1,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,  2,100,100,100,100},
     {  2,  2,  2,  2,  2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,  2,101,101,101,101},
     {102,102,  3,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,  4,102,102,102,102,102,102,102},
     {501,501,  5,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
     {103,103,  5,  6,  6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
     {502,502,  8,502,502,  7,  7,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
     {503,503,  8,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
     {104,104,  8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
     {  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,106,  9,  9,  9,  9,  9,  9,  9,  9,509},
     {113,113,113,113,113,113,113,113,113,113,113,113,112,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
     {114,114,114,114,114,114,114,114,114,114,114,114,115,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114},
     {116,116,116,116,116,116,116,116,116,116,116,116,117,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116},
     {118,118,118,118,118,118,118,118,118,118,118,118,119,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118},
     {505,505,505,505,505,505,505,505,505,505,505,505,505,505,120,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505},
     {506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,121,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506},
     { 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,504, 17, 17, 17, 17, 17, 17, 17, 17, 17,507},
     {507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,105,507,507,507,507,507,507,507,507,507,507}};

     bool cont=false;
     int state;             //state serves to know wich state am on
     int column;            //column serves to point the column of the state matrix that im going to move
     int index;             //index serves to point the character im about to evaluate
     char readChar;         //readChar serves to save the character im evaluating
     string input;          //input serves to store the full string that was input in the editor
     QString lexicLog = ""; //lexicLog serves to store the message associated with a terminal state
     string aux = "";       //aux serves to save the word im analyzing



public:

     void readFile(){

         QString file=QFileDialog::getOpenFileName(this, tr("Open File"),"C:\\","COVID Files (*.cvd)" );
         string cadena;
            this->ui->consola->setMarkdown("");
            this->ui->editor->setMarkdown("");
            ifstream datos(file.toStdString()); //change route as required
                 if(datos.fail()){
                    this->ui->consola->setMarkdown("Missing the archive named \"Analizador.cvd\"");
                 }else{
            while(!datos.eof()){
               getline(datos,cadena); //in this method you take the string (delimitated by any \n)
                this->ui->editor->append(QString::fromStdString(cadena));
               this->ui->consola->setMarkdown("File loaded");

           }
        }
     }


     void saveFile(){
        QString file=QFileDialog::getOpenFileName(this, tr("Save File"),"C:\\","COVID Files (*.cvd)" );
        ofstream fs(file.toStdString()); //change route as required
        fs << ui->editor->toPlainText().toStdString() << endl;
        this->ui->consola->setMarkdown("");
        this->ui->consola->setMarkdown("File saved");
        fs.close();
     }

void scan(int ind)
{   //initialize everything for a new lexical analice
    input="";
    aux="";
    lexicLog = "";

    input=ui->editor->toPlainText().toStdString();
    input+="~";
    this->ui->consola->setMarkdown("");

    state = 0; //set initial state always to 0

    //initialize everything for a new lexical analice
    int tam=input.size(); //aquire the lenght of the lenguage element being analized
    int pst=0;
    while( state <= 17 && ind < tam) { //the while cicle with validate that im not on a terminal state, nor im out of chars to evaluate

          readChar = getCharacter(ind);     //execute the method getChar to extract the char at local index variable
          aux += readChar;                  //add this char to the aux var
          column = relate(readChar, state); //execute relate
          pst = state;
          state = stateMat[state][column];  //var state will now get to the next "state" according to the cross reference on the stateMat

          if(readChar == '~' && pst>100){
              state=200;
          }

            if(state == 0 ) {//this to validate no spaces, /t or /n where stored on the aux var
                    aux = "";//provided of course that is the first element since is the only one that can go to the 0 state
            }

          ind++;             //ind local var increases
          this->index = ind; //thus updating the atribute index for global use on this class



          if( state >= 100 && state <= 131){            //if we reach a validation state -start
              if(state == 100){                 //if we reach a reserved word state -start
                 state = getReservedWord(aux.substr(0 , aux.size()-1));
              }                                 //if we reach a reserved word state -end
                    if(state==105
                            || state==106
                            || state==112
                            || state==115
                            || state==117
                            || state==119
                            || state==120
                            || state==121){//"asdasdas" or 'C'
                        aux = aux.substr(0 , aux.size());
                    }else{
                        aux = aux.substr(0 , aux.size()-1);
                 }
              lexicLog=getToken(state, readChar, aux);
              this->ui->consola->append(lexicLog);  //display the token message on the console part of the interface

                                                        //if we reach a validation state -end
          } else{
              if(state >= 500 && readChar!='~') {                            //if we encounter an error state -start
                  lexicLog= getError(state);
                  this->ui->consola->append(lexicLog);  //display the token message on the console part of the interface

              }else {
                  if(state >500){
                      lexicLog= getError(state);
                      this->ui->consola->append(lexicLog);

                  }
              }                                                                //if we encounter an error state -end
          }

          if((state>=100 && state<500) && readChar != '~'){//provided we've reached an ending state and there are still elements to evaluate -start



            if(aux!=""
                   && (state==100
                    || state==101
                    || state==102
                    || state==103
                    || state==104
                    || state==113
                    || state==114
                    || state==116
                    || state==119)){
                ind-=1;
            }
            state=0;
            aux = "";                                                        // ind local index
          this->index = ind;
          }                                 //provided we've reached an ending state and there are still elements to evaluate -end

    if(readChar == '~'){
        state=200;
        this->ui->consola->append("<ENDING>");
    }

    }
}//end analyze


             char getCharacter(int ind){
                 return this->input[ind];
             }

             int relate(char character, int sta) {
                 //this method serves to point wich column am I going to focus based on the char input
                 if(character == 'E' && sta==5) {
                    return 3;
                 } if(character == 'e' && sta==5) {
                    return 4;
                 } if(character >= 'a' && character <='z') {
                    return 1;
                 } if(character >= 'A' && character <='Z') {
                    return 0;
                 } if(character >= '0' && character <='9') {
                    return 2;
                 }

                 switch(character){
                 case '+' :  return 5;
                 case '-' :  return 6;
                 case '*' :  return 7;
                 case '/' :  return 8;
                 case '%' :  return 9;
                 case '<' : return 10;
                 case '>' : return 11;
                 case '=' : return 12;
                 case '!' : return 13;
                 case '&' : return 14;
                 case '|' : return 15;
                 case '(' : return 16;
                 case ')' : return 17;
                 case '[' : return 18;
                 case ']' : return 19;
                 case '{' : return 20;
                 case '}' : return 21;
                 case '\'': return 22;
                 case '"' : return 23;
                 case ';' : return 24;
                 case '.' : return 25;
                 case ':' : return 26;
                 case ',' : return 27;
                 case '_' : return 28;
                 case ' ' : return 29;
                 case '\t': return 30;
                 case '\n': return 31;
                 case '~' : return 32;
                 default  : return 32;











                 }
             }

             QString getError(int edo){
                    switch(edo){
                        case 500: return "Error 500, unknown simbol";
                        case 501: return "Error 501, missing digit";
                        case 502: return "Error 502, incomplete scientific notation";
                        case 503: return "Error 503, missing digit";
                        case 504: return "Error 504, missing character";
                        case 505: return "Error 505, missing ampersand";
                        case 506: return "Error 506, missing pleca";
                        case 507: return "Error 507, missing apostrophe ";
                        case 508: return "Error 508, you can't start with a \"_\" simbol";
                        case 509: return "Error 509, missing quote ";
                        default : return "getError() default case: \"Not error id\"\n ¿How did we get here when I used to know you so well?";
                    }
                }//end getError

            int getReservedWord(string temp){
                //this method validates that the string recived belongs to the reserved words of the lenguage thus keeping the 100 state

                if(temp=="class"
                        || temp=="for"
                        || temp=="while"
                        || temp=="do"
                        || temp=="if"
                        || temp=="then"
                        || temp=="else"
                        || temp=="elseif"
                        || temp=="switch"
                        || temp=="case"
                        || temp=="def"
                        || temp=="import"
                        || temp=="int"
                        || temp=="float"
                        || temp=="char"
                        || temp=="string"
                        || temp=="input"
                        || temp=="print"
                        || temp=="for"
                        ){
                    return 100;
                }else{
                    //provided that the word doesn't belong in the list, the state is updated to 101 being classified as an identifier
                    return 101;
                }

               }//end getReservedWord
         QString getToken(int state, char character, string aux){
                 //this method serves to get the token class and message that suits the analyzed string
                    string estado="";//estado serves to store said token class and message in cases were we analize only one character
                    char est=input[index-2];
                    switch(state){
                        case 100: return QString::fromStdString("100 : <" + aux + " its a reserved_word>\n");
                    case 101: if(aux.size()!=1){
                            return QString::fromStdString("101 : <" + aux + " its an identifier>\n");
                        }else{
                            estado="101 : [";
                            estado+=est;
                            estado+= "  its an identifier]\n";
                        }
                            return QString::fromStdString(estado); //+
                        case 102: return QString::fromStdString("102 : <" + aux + " its an integer>\n");
                        case 103: return QString::fromStdString("103 : <" + aux + " its a float_number>\n");
                        case 104: return QString::fromStdString("104 : <" + aux + " its a scientific_notation_number>\n");
                        case 105: return QString::fromStdString("105 : <" + aux + " its a char>\n");
                        case 106: return QString::fromStdString("106 : <" + aux + " its a string>\n");
                        case 107: estado="107 : <";
                                  estado+=character;
                                  estado+= " its an aritmetic_operator>\n";
                                    return QString::fromStdString(estado); //+
                        case 108: estado="108 : <";
                                  estado+=character;
                                  estado+= " its an aritmetic_operator>\n";
                                    return QString::fromStdString(estado); //-
                        case 109: estado="109 : <";
                                  estado+=character;
                                  estado+= " its an aritmetic_operator>\n";
                                    return QString::fromStdString(estado); // *
                        case 110: estado="110 : <";
                                  estado+=character;
                                  estado+= " its an aritmetic_operator>\n";
                                    return QString::fromStdString(estado); // /
                        case 111: estado="111 : <";
                                  estado+=character;
                                  estado+= " its an aritmetic_operator>\n";
                                    return QString::fromStdString(estado); // %
                        case 112: return QString::fromStdString("112 : <" + aux + " its a relational_operator>\n"); // ==
                        case 113: return QString::fromStdString("113 : <" + aux + " its an assignment_operator>\n"); // =
                        case 114: return QString::fromStdString("114 : [" + aux + " its a relational_operator]\n"); // >
                        case 115: return QString::fromStdString("115 : [" + aux + " its a relational_operator]\n"); // >=
                        case 116: return QString::fromStdString("116 : [" + aux + " its a relational_operator]\n"); // <
                        case 117: return QString::fromStdString("117 : [" + aux + " its a relational_operator]\n"); // <=
                        case 118: return QString::fromStdString("118 : <" + aux + " its a logic_operator_NOT>\n"); // !
                        case 119: return QString::fromStdString("119 : <" + aux + " its a relational_operator>\n"); // !=
                        case 120: return QString::fromStdString("120 : <" + aux + " its a logic_operator_AND>\n"); // &&
                        case 121: return QString::fromStdString("121 : <" + aux + " its a logic_operator_OR>\n"); // ||
                        case 123: estado= "122 : <";
                                  estado+= character;
                                  estado+= " its an opening_parenthesis>\n"; // (
                                  return QString::fromStdString(estado);
                        case 122: estado= "123 : <" ;
                                  estado+= character;
                                  estado+= " its a closing_parenthesis>\n"; // )
                                  return QString::fromStdString(estado);
                        case 124: estado= "124 : <";
                              estado+= character;
                              estado+= " its an opening_curly_brace>\n"; // {
                              return QString::fromStdString(estado);
                        case 125: estado= "125 : <" ;
                              estado+= character;
                              estado+= " its a closing_curly_brace>\n";// }
                              return QString::fromStdString(estado);
                         case 126: estado= "126 : <";
                                  estado+= character;
                                  estado+= " its an opening_square_bracket>\n"; // [
                                  return QString::fromStdString(estado);
                        case 127: estado= "127 : <";
                                  estado+= character;
                                  estado+= " its a closing_square_bracket>\n"; // ]
                                  return QString::fromStdString(estado);                                                      
                        case 128: estado= "128 : <" ;
                                 estado+= character;
                                 estado+= " its a semicolon>\n";// ;
                                 return QString::fromStdString(estado);
                        case 129: estado= "129 : <" ;
                              estado+= character;
                              estado+= " its a dot>\n";// .
                              return QString::fromStdString(estado);                              
                        case 130: estado= "130 : <" ;
                             estado+= character;
                             estado+= " its a colon> \n";// :
                             return QString::fromStdString(estado);                                
                        case 131: estado= "131 : <" ;
                            estado+= character;
                            estado+= " its a comma\n";// ,
                            return QString::fromStdString(estado);                                    
                        default: return "FILE_ENDING";
                    }
                }//end getToken

private slots:
         //void on_pushButton_clicked();
         void on_an_clicked();
         void on_open_clicked();
         void on_save_clicked();
};
#endif // MAINWINDOW_H
