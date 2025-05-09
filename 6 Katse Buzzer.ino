// Meloodiate mängimine.

// Käsk Arduino tone() - noote tihedus.

// Noodid:

// note 	frequency

// c     262 Hz

// d     294 Hz

// e     330 Hz

// f     349 Hz

// g     392 Hz

// a     440 Hz

// b     494 Hz

// C     523 Hz

const int buzzerPin = 9;

// pikkus on nootide ja pausite koguste summa

const int songLength = 18;

char notes[] = "cdfda ag cdfdg gf "; // tähed on noodid ja tühik on paus

// Rütmi seadistamine.

int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

// "tempo" meloodia kiirus. Kui väiksem tempo_ siis suurem kiirus.

int tempo = 150;

void setup() 

{

  pinMode(buzzerPin, OUTPUT);

}

void loop() 

{

  int i, duration;

  for (i = 0; i < songLength; i++)

  {

    duration = beats[i] * tempo; 

    if (notes[i] == ' ')          // kui noot puudub

    {

      delay(duration);          

    }

    else                         

    {

      tone(buzzerPin, frequency(notes[i]), duration);

      delay(duration);          

    }

    delay(tempo/10);              // väike paus nootide vahel

  }

  while(true){}

}

int frequency(char note) 

{

  int i;

  const int numNotes = 8;  // nootide kogus

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };

  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  // kui noot on olemas, siis tagastame selle tiheduse 

  for (i = 0; i < numNotes; i++)  

  {

    if (names[i] == note)       

    {

      return(frequencies[i]);    

    }

  }

  return(0); 

}
