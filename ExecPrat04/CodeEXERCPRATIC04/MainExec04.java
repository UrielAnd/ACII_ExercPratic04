import java.io.*;
import java.util.*;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Autor: @Uriel Andrade 
         @Arthur Gomes
         @Thiago Utsch
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public class MainExec04 {
    protected static Scanner sc = new Scanner(System.in);
    protected static Map<String, Integer> auxMnemonicos = new HashMap<>();

    public static void main(String[] args){
        try {
            Scanner inputFile;
            controlMnemonicos();

            System.out.print("Type the name of the root file: ");
            String Name = sc.next();
            inputFile = new Scanner(new FileReader(Name));

            //Lista dos códigos hexadecimais gerados//


            List<String> listExpressions = readFile(inputFile);

            //Gera um novo arquivo com o mesmo nome, mas com extensão .hex//


            String outputFileName = Name.substring(0, Name.lastIndexOf('.')+1) + "hex";
            createResultFile(listExpressions, outputFileName);
            System.out.println("A file called \"" + outputFileName.substring(outputFileName.lastIndexOf("\\")+1) + "\" was generated in the directory: " +  outputFileName.substring(0, outputFileName.lastIndexOf("\\")));

            inputFile.close();
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public static List<String> readFile(Scanner scanner){
        List<String> hexExpressions = new ArrayList<>();
        Integer aValue = 0;
        Integer bValue = 0;
        String line;

        while(scanner.hasNext()){
            line = scanner.nextLine();
            line = line.replace("\n", "").replace(" ","");                         //Padroniza as linhas//
            if(!(line.equals("inicio:") || line.equals("fim."))) {                                                  //Caso o conteúdo da linha seja 'inicio:' ou 'fim.', se for 'fim.' o programa termina//
                char charAux = line.charAt(0);
                if (charAux == 'X') {                           //Char 'X' representa o valor de A// 
                    char charValue = line.charAt(2);
                    aValue = charValue >= 48 && charValue <= 57 ? (int) charValue - 48 : (int) charValue - 55;      //Transforma o char em um número decimal//
                } else if (charAux == 'Y') {
                    char charValue = line.charAt(2);            //Char 'Y' representa o valor de B
                    bValue = charValue >= 48 && charValue <= 57 ? (int) charValue - 48 : (int) charValue - 55;      //Transforma o char em um número decimal//
                } else {                                        //Char 'W' ou outro representa a operação
                    String mnemonico = line.substring(2, line.lastIndexOf(';'));                                //Extrai o mnemônico da linha//

                    //A próxima linha transforma a representação decimal em uma representação de caracteres hexadecimais de A e B//
                    //Ele também pega o valor decimal do mnemônico e o transforma em uma representação de caractere hexadecimal//
                    hexExpressions.add(new StringBuilder().append(Hexa(aValue)).append(Hexa(bValue)).append(Hexa(auxMnemonicos.get(mnemonico))).toString());
                }
            } else if(line.equals("fim.")){
                break;
            }
        }

        return hexExpressions;
    }

    //Referencia os valores decimais de cada sentença mnemônica//
    public static void controlMnemonicos(){
        auxMnemonicos.put("An", 0);
        auxMnemonicos.put("nAoB", 1);
        auxMnemonicos.put("AnB", 2);
        auxMnemonicos.put("zeroL", 3);
        auxMnemonicos.put("nAeB", 4);
        auxMnemonicos.put("Bn", 5);
        auxMnemonicos.put("AxB", 6);
        auxMnemonicos.put("ABn", 7);
        auxMnemonicos.put("AnoB", 8);
        auxMnemonicos.put("nAxB", 9);
        auxMnemonicos.put("copiaB", 10);
        auxMnemonicos.put("AB", 11);
        auxMnemonicos.put("umL", 12);
        auxMnemonicos.put("AoBn", 13);
        auxMnemonicos.put("AoB", 14);
        auxMnemonicos.put("copiaA", 15);
    }

    //Transforma um inteiro em um caractere hexadecimal//
    public static Character Hexa(Integer  value){
        return (value < 10) ? value.toString().charAt(0) : ((char) (value + 55));
    }

    public static void createResultFile(List<String> result, String Name) throws IOException{
        BufferedWriter LOR;
        try{
            LOR = new BufferedWriter(new FileWriter(Name));
        } catch (Exception e){
            e.printStackTrace();
            return;
        }

        //Escreva no arquivo as operações geradas//
        try {
            result.forEach(expression -> {
                try {
                    LOR.write(expression + "\n");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
            //O caso final é 'FIM', então é a última operação no arquivo//
            LOR.write("FIM");
        } catch (Exception e){
            e.printStackTrace();
        }

        LOR.close();
    }

}
