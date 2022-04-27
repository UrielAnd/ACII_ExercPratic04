#define MAX_MEMORIA 100

const int led13 = 13;
const int led12 = 12;
const int led11 = 11;
const int led10 = 10;

String memoria[MAX_MEMORIA];

int contador = 4;

void setup()
{
  Serial.begin(9600);

  pinMode(led13, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led10, OUTPUT);
}

void loop()
{
  if (Serial.available() == 3)
  {
    String input = Serial.readString();

    if (contador < MAX_MEMORIA)
    {

      if (input.compareTo("executa") == 0 || input.compareTo("executar") == 0)
      {
        executaPrograma();
        contador = MAX_MEMORIA;
        return;
      }
      // memoria[1] = input.charAt(0);
      // memoria[2] = input.charAt(1);
      // memoria[3] = input.charAt(2);

      memoria[contador++] = input;

      Serial.print("Memoria: ");
      Serial.println();
      printaMemoria();
    }
    else
    {
      Serial.print("Memoria esgotada");
      executaPrograma();
      Serial.println();
    }
  }
}

byte portaXor(byte a, byte b)
{
  return (a ^ b);
}

byte portaOr(byte a, byte b)
{
  return (a | b);
}

byte portaAnd(byte a, byte b)
{
  return (a & b);
}

byte portaNot(byte a)
{
  a = ~a;
  a >>= 4;
  return a;
}

void setPinos()
{
  const byte result = stringToByte(memoria[0]);
  switch (result)
  {
  case 0:
    setPino(0, 0, 0, 0);
    break;
  case 1:
    setPino(0, 0, 0, 1);
    break;
  case 2:
    setPino(0, 0, 1, 0);
    break;
  case 3:
    setPino(0, 0, 1, 1);
    break;
  case 4:
    setPino(0, 1, 0, 0);
    break;
  case 5:
    setPino(0, 1, 0, 1);
    break;
  case 6:
    setPino(0, 1, 1, 0);
    break;
  case 7:
    setPino(0, 1, 1, 1);
    break;
  case 8:
    setPino(1, 0, 0, 0);
    break;
  case 9:
    setPino(1, 0, 0, 1);
    break;
  case 10:
    setPino(1, 0, 1, 0);
    break;
  case 11:
    setPino(1, 0, 1, 1);
    break;
  case 12:
    setPino(1, 1, 0, 0);
    break;
  case 13:
    setPino(1, 1, 0, 1);
    break;
  case 14:
    setPino(1, 1, 1, 0);
    break;
  case 15:
    setPino(1, 1, 1, 1);
    break;

  default:
    break;
  }
}

void setPino(byte F3, byte F2, byte F1, byte F0)
{
  if (F3 == 0)
    digitalWrite(led13, LOW);
  else
    digitalWrite(led13, HIGH);

  if (F2 == 0)
    digitalWrite(led12, LOW);
  else
    digitalWrite(led12, HIGH);

  if (F1 == 0)
    digitalWrite(led11, LOW);
  else
    digitalWrite(led11, HIGH);

  if (F0 == 0)
    digitalWrite(led10, LOW);
  else
    digitalWrite(led10, HIGH);
}

byte stringToByte(String hex)
{
  if (hex.compareTo("0") == 0)
  {
    return 0;
  }
  if (hex.compareTo("1") == 0)
  {
    return 1;
  }
  if (hex.compareTo("2") == 0)
  {
    return 2;
  }
  if (hex.compareTo("3") == 0)
  {
    return 3;
  }
  if (hex.compareTo("4") == 0)
  {
    return 4;
  }
  if (hex.compareTo("5") == 0)
  {
    return 5;
  }
  if (hex.compareTo("6") == 0)
  {
    return 6;
  }
  if (hex.compareTo("7") == 0)
  {
    return 7;
  }
  if (hex.compareTo("8") == 0)
  {
    return 8;
  }
  if (hex.compareTo("9") == 0)
  {
    return 9;
  }
  if (hex.compareTo("A") == 0)
  {
    return 10;
  }
  if (hex.compareTo("B") == 0)
  {
    return 11;
  }
  if (hex.compareTo("C") == 0)
  {
    return 12;
  }
  if (hex.compareTo("D") == 0)
  {
    return 13;
  }
  if (hex.compareTo("E") == 0)
  {
    return 14;
  }
  if (hex.compareTo("F") == 0)
  {
    return 15;
  }
}

String byteToString(byte number)
{
  switch (number)
  {
  case 0:
    return "0";
    break;
  case 1:
    return "1";
    break;
  case 2:
    return "2";
    break;
  case 3:
    return "3";
    break;
  case 4:
    return "4";
    break;
  case 5:
    return "5";
    break;
  case 6:
    return "6";
    break;
  case 7:
    return "7";
    break;
  case 8:
    return "8";
    break;
  case 9:
    return "9";
    break;
  case 10:
    return "A";
    break;
  case 11:
    return "B";
    break;
  case 12:
    return "C";
    break;
  case 13:
    return "D";
    break;
  case 14:
    return "E";
    break;
  case 15:
    return "F";
    break;

  default:
    break;
  }
}

String ULA()
{
  String X = memoria[1];
  String Y = memoria[2];
  String S = memoria[3];

  const byte operation = stringToByte(S);

  const byte A = stringToByte(X);
  const byte B = stringToByte(Y);

  byte retorno;

  switch (operation)
  {
  case 0:
    retorno = portaNot(A);
    break;

  case 1:
    retorno = portaNot(portaOr(A, stringToByte(Y)));
    break;

  case 2:
    retorno = portaAnd(portaNot(A), stringToByte(Y));
    break;

  case 3:
    retorno = 0;
    break;

  case 4:
    retorno = portaNot(portaAnd(A, B));
    break;

  case 5:
    retorno = portaNot(B);
    break;

  case 6:
    retorno = portaXor(A, B);
    break;

  case 7:
    retorno = portaAnd(A, portaNot(B));
    break;

  case 8:
    retorno = portaOr(portaNot(A), B);
    break;

  case 9:
    retorno = portaNot(portaXor(A, B));
    break;

  case 10:
    retorno = B;
    break;

  case 11:
    retorno = portaAnd(A, B);
    break;

  case 12:
    retorno = 15;
    break;

  case 13:
    retorno = portaOr(A, portaNot(B));
    break;

  case 14:
    retorno = portaOr(A, B);
    break;

  case 15:
    retorno = A;
    break;
  }

  return byteToString(retorno);
}

void printaMemoria()
{
  // print memoria
  Serial.println();
  Serial.print("[");
  for (int i = 0; i < MAX_MEMORIA; i++)
  {
    Serial.print(memoria[i]);

    if (i < MAX_MEMORIA - 2)
      Serial.print(" | ");
  }
  Serial.print("]");
  Serial.println();
}

void executaPrograma()
{
  Serial.print("Memoria antes da execucao: ");
  printaMemoria();

  // executa programa
  for (int i = 4; i < contador; i++)
  {
    memoria[1] = memoria[i].charAt(0);
    memoria[2] = memoria[i].charAt(1);
    memoria[3] = memoria[i].charAt(2);

    memoria[0] = ULA();

    Serial.print(memoria[i] + ": ");
    Serial.print(memoria[0]);
    Serial.println();

    setPinos();
    delay(2000);
  }

  Serial.print("Memoria depois da execucao: ");
  printaMemoria();
}

// 003
// 00C
// 006
// 001
// 00E
// 005
// 003
// 00D
// 003
// 000
// 003
// FFF
// 1FF

