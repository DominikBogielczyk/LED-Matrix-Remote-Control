#include <LedControl.h>

#define DIN 10
#define CS 9
#define CLK 8

LedControl lc = LedControl(DIN, CLK, CS, 4);  //LedControl(dataPin,clockPin,csPin,numDevices)

String modes = "    ";  //'h' - heart, 'p' - pacman, 's' - stairs, 't' - text

//patterns
byte heart_pattern[7] = {0x66, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18};
byte pacman1[7] = {0x38, 0x44, 0x88, 0x90, 0x88, 0x44, 0x38};
byte pacman2[7] = {0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38};
byte numbers[10][5] = {
  {0x07, 0x05, 0x05, 0x05, 0x07}, // 0
  {0x01, 0x01, 0x01, 0x01, 0x01}, // 1
  {0x07, 0x01, 0x07, 0x04, 0x07}, // 2
  {0x07, 0x01, 0x07, 0x01, 0x07}, // 3
  {0x05, 0x05, 0x07, 0x01, 0x01}, // 4
  {0x07, 0x04, 0x07, 0x01, 0x07}, // 5
  {0x07, 0x04, 0x07, 0x05, 0x07}, // 6
  {0x07, 0x01, 0x01, 0x01, 0x01}, // 7
  {0x07, 0x05, 0x07, 0x05, 0x07}, // 8
  {0x07, 0x05, 0x07, 0x01, 0x07}  // 9
};
byte dice5[3] = {0xA0, 0x40, 0xA0};
byte dice6[3] = {0xA0, 0xA0, 0xA0};

//letters
byte letters[26][7] = {                       // ASCII TABLE: 65 - 'A', 66 - 'B', ...
  {0x38, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44}, // A
  {0x3C, 0x22, 0x22, 0x3C, 0x22, 0x22, 0x3C}, // B
  {0x1C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x1C}, // C
  {0x38, 0x24, 0x22, 0x22, 0x22, 0x24, 0x38}, // D
  {0x3E, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x3E}, // E
  {0x3E, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x20}, // F
  {0x1C, 0x22, 0x20, 0x2E, 0x22, 0x22, 0x1E}, // G
  {0x22, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22}, // H
  {0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C}, // I
  {0x38, 0x08, 0x08, 0x08, 0x08, 0x28, 0x18}, // J
  {0x22, 0x24, 0x28, 0x30, 0x28, 0x24, 0x22}, // K
  {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E}, // L
  {0x22, 0x36, 0x2A, 0x2A, 0x22, 0x22, 0x22}, // M
  {0x22, 0x22, 0x32, 0x2A, 0x26, 0x22, 0x22}, // N
  {0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C}, // O
  {0x3C, 0x22, 0x22, 0x3C, 0x20, 0x20, 0x20}, // P
  {0x1C, 0x22, 0x22, 0x22, 0x2A, 0x24, 0x1A}, // Q
  {0x3C, 0x22, 0x22, 0x3C, 0x28, 0x24, 0x22}, // R
  {0x1E, 0x20, 0x20, 0x1C, 0x02, 0x02, 0x3C}, // S
  {0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08}, // T
  {0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C}, // U
  {0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x08}, // V
  {0x22, 0x22, 0x22, 0x2A, 0x2A, 0x2A, 0x14}, // W
  {0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22}, // X
  {0x22, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08}, // Y
  {0x3E, 0x02, 0x04, 0x08, 0x10, 0x20, 0x3E}  // Z
};

byte zero_big[7] = {0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C};
byte one_big[7] = {0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x1C};
byte two_big[7] = {0x1C, 0x02, 0x02, 0x04, 0x08, 0x10, 0x1E};
byte three_big[7] = {0x3E, 0x04, 0x08, 0x04, 0x02, 0x22, 0x1C};
byte four_big[7] = {0x04, 0x0C, 0x14, 0x24, 0x3E, 0x04, 0x04};
byte five_big[7] = {0x3E, 0x20, 0x3C, 0x02, 0x02, 0x02, 0x3C};
byte six_big[7] = {0x0C, 0x10, 0x20, 0x3C, 0x22, 0x22, 0x1C};
byte seven_big[7] = {0x3E, 0x22, 0x02, 0x04, 0x08, 0x08, 0x08};
byte eight_big[7] = {0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x1C};
byte nine_big[7] = {0x1C, 0x22, 0x22, 0x1E, 0x02, 0x04, 0x18};
byte *numbers_big[10] = {zero_big, one_big, two_big, three_big, four_big, five_big, six_big, seven_big, eight_big, nine_big};

bool matrixes[4] = {0, 0, 0, 0};
bool heart_state = 0;
unsigned long heart_t = millis();
unsigned long stairs_t = millis();
unsigned long pacman_t = millis();
unsigned long text_t = millis();
unsigned long random_num_t = millis();
uint8_t stairs_i = 0;
uint8_t pacman_i = 0;
uint8_t text_i = 0;
uint8_t prescaler = 4; //gif changing freq prescaler
String entered_text = "";

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    lc.shutdown(i, false);  //wake up the MAX7219 from power-saving mode
    lc.setIntensity(i, 1);  //address, intensity (0-15)
    lc.clearDisplay(i);
  }

  randomSeed(analogRead(0)); //random generator initialization, noise from analog input
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
    receive_data();

  //GIFs
  for (int i = 0; i < modes.length(); i++)
  {
    if (modes.indexOf('s') != -1 and millis() - stairs_t >= 4000 / prescaler) //stairs
      stairs();
    if (modes.indexOf('p') != -1 and millis() - pacman_t >= 2000 / prescaler)
      pacman();
    if (modes.indexOf('h') != -1 and millis() - heart_t >= 2000 / prescaler)
      heart(heart_state);
    if (modes.indexOf('r') != -1 and millis() - random_num_t >= 4000 / prescaler)
      random_pattern();
    if (modes.indexOf('t') != -1 and millis() - text_t >= 3000 / prescaler)
      display_text(entered_text, text_i);
  }
}

void receive_data()
{
  String received_data = Serial.readString();
  String cmd[4] = {"ch1", "ch2", "ch3", "ch4"};

  for (int i = 0; i < 4; i++)
  {
    if (received_data.indexOf(cmd[i]) != -1)  //TOGGLE SCREEN ON/OFF STATE
      matrixes[i] = !matrixes[i];
  }

  if (received_data.indexOf("sl") != -1 and prescaler >= 1 and prescaler <= 9) //SLIDER HANDLE
    prescaler = received_data[received_data.indexOf("sl") + 2] - 48; //from ACII table '0' = 48, '1' = 49, ...

  if (received_data.indexOf("dice") != -1)
    dice();
  else if (received_data.indexOf("snake") != -1)
    snake();
  else if (received_data.indexOf("draw") != -1)
    random_numbers();
  else if (received_data.indexOf("*") != -1)
  {
    entered_text = received_data.substring(received_data.indexOf("*") + 1);
    entered_text.toUpperCase();
    text_i = 0;
  }
  else if (received_data.length() > 0)
  {
    String tab[5] = {"heart", "pacman", "stairs", "random", "text"};

    for (int j = 0; j < sizeof(tab) / sizeof(tab[0]); j++)
    {
      if (received_data.indexOf(tab[j]) != -1)
      {
        if (received_data == "text")
          modes = "tttt";
        else
        {
          for (int i = 0; i < 4; i++)
          {
            if (matrixes[i])
              modes[i] = tab[j][0];
          }
        }
      }
    }
  }
  else if (received_data.indexOf("clear") != -1)
    clear();
}

void print_pattern(byte *value, uint8_t n, uint8_t addr)
{
  if (n < 8) lc.clearDisplay(addr);

  for (int i = 0; i < n; i++)
  {
    lc.setRow(addr, i, value[i]);
  }
}

void heart(bool state)
{
  for (int i = 0; i < 4; i++)
  {
    if (modes[i] == 'h')
      state == 1 ? print_pattern(heart_pattern, sizeof(heart_pattern), i) : lc.clearDisplay(i);
  }
  heart_state = !state; //TOGGLE HEART STATE
  heart_t = millis();
}

void pacman()
{
  if (pacman_i == 0)
  {
    for (int i = 0; i < 4; i++)
    {
      if (modes[i] == 'p') print_pattern(pacman1, sizeof(pacman1), i); //FIRST FRAME}
    }
  }
  else if (pacman_i >= 0 and pacman_i < 4)
  {
    for (int j = 0; j < 4; j++)
    {
      if (modes[j] == 'p')
      {
        lc.setLed(j, 3, 7 - pacman_i, 1);
        lc.setLed(j, 3, 7 - pacman_i + 1, 0);
      }
    }
  }
  else // pacman_i == 4 - END FRAME
  {
    for (int i = 0; i < 4; i++)
    {
      if (modes[i] == 'p') print_pattern(pacman2, sizeof(pacman2), i);
    }
  }
  pacman_i++;
  if (pacman_i == 5) pacman_i = 0;
  pacman_t = millis();
}

void random_numbers()
{
  reset_mode();
  for (int i = 0; i < 10; i++) //10 RANDOM NUMBERS
  {
    for (int j = 0; j < 4; j++)
    {
      if (matrixes[j])
      {
        uint8_t v1 = random(10); // Generates a random number between 0 and 9
        uint8_t v2 = random(10);
        byte x[7] = {};
        for (int i = 0; i < 5; i++)
        {
          x[i + 2] = (numbers[v1][i] << 4) + numbers[v2][i];
        }
        print_pattern(x, sizeof(x), j);
      }
    }
    delay(100);
  }
}

void dice()
{
  reset_mode();
  for (int j = 0; j < 7; j++) //7 DICES ANIMATIONS
  {
    for (int k = 0; k < 4; k++)
    {
      if (matrixes[k])
      {
        lc.clearDisplay(k);
        uint8_t v[2] = {random(1, 7), random(1, 7)}; // 2x <1; 6>

        for (int i = 0; i < 2; i++)
        {
          switch (v[i])
          {
            case 1:
              lc.setLed(k, 1 + 5 * i, 1 + 5 * i, 1);
              break;
            case 2:
              lc.setLed(k, 0 + 5 * i, 0 + 5 * i, 1);
              lc.setLed(k, 2 + 5 * i, 2 + 5 * i, 1);
              break;
            case 3:
              lc.setLed(k, 0 + 5 * i, 0 + 5 * i, 1);
              lc.setLed(k, 1 + 5 * i, 1 + 5 * i, 1);
              lc.setLed(k, 2 + 5 * i, 2 + 5 * i, 1);
              break;
            case 4:
              lc.setLed(k, 0 + 5 * i, 0 + 5 * i, 1);
              lc.setLed(k, 2 + 5 * i, 0 + 5 * i, 1);
              lc.setLed(k, 0 + 5 * i, 2 + 5 * i, 1);
              lc.setLed(k, 2 + 5 * i, 2 + 5 * i, 1);
              break;
            case 5:
              lc.setRow(k, 0 + 5 * i, dice5[0] >> (5 * i));
              lc.setRow(k, 1 + 5 * i, dice5[1] >> (5 * i));
              lc.setRow(k, 2 + 5 * i, dice5[2] >> (5 * i));
              break;
            case 6:
              lc.setRow(k, 0 + 5 * i, dice6[0] >> (5 * i));
              lc.setRow(k, 1 + 5 * i, dice6[1] >> (5 * i));
              lc.setRow(k, 2 + 5 * i, dice6[2] >> (5 * i));
              break;
          }
        }
      }
    }
    delay(200);
  }
}

void stairs()
{
  if (stairs_i == 0) //FIRST FRAME - CLEAR DISPLAY
  {
    for (int i = 0; i < 4; i++)
    {
      if (modes[i] == 's') lc.clearDisplay(i);
    }
  }

  for (int j = 7; j >= stairs_i; j--)  //NEXT FRAMES
  {
    for (int k = 0; k < 4; k++)
    {
      if (modes[k] == 's') lc.setLed(k, j, stairs_i, 1);
    }
  }
  stairs_i++;
  if (stairs_i == 8) stairs_i = 0;
  stairs_t = millis();
}

int snake()
{
  uint8_t pos_x[30] = {3, 4, 5, 6};
  uint8_t pos_y[30] = {4, 4, 4, 4};
  uint8_t fruit[3] = {(uint8_t) random(24), (uint8_t) random(8)};
  uint8_t snake_size = 4;
  String dir = "left";
  unsigned long prev_time = millis();
  bool end_game = false;

  clear();

  //SNAKE FIRST DRAW
  for (int i = 0; i < snake_size - 1; i++)
  {
    lc.setLed(3 - pos_x[i] / 8, pos_y[i], pos_x[i] % 8, 1);
  }

  //FRUIT FIRST DRAW
  lc.setLed(3 - fruit[0] / 8, fruit[1], fruit[0] % 8, 1);

  while (!end_game)
  {
    if (millis() - prev_time >= (unsigned long) 500)
    {
      prev_time = millis();

      //SNAKE MOVEMENT
      uint8_t last_x = pos_x[snake_size - 1];
      uint8_t last_y = pos_y[snake_size - 1];

      for (int i = snake_size - 1; i >= 1; i--)
      {
        pos_x[i] = pos_x[i - 1];
        pos_y[i] = pos_y[i - 1];
      }

      if (fruit[1] == pos_y[0] && fruit[0] == pos_x[0])	//SNAKE EATS FRUIT
      {
        bool unique = 0;

        while (!unique)
        {
          fruit[0] = random(24);
          fruit[1] = random(8);
          bool unique_x = 1;
          bool unique_y = 1;

          for (int i = 0; i < snake_size; i++)
          {
            if (pos_x[i] == fruit[0])
              unique_x = 0;
            if (pos_y[i] == fruit[1])
              unique_y = 0;
          }
          unique = unique_x and unique_y;
        }

        snake_size ++;

        //FRUIT DRAW
        lc.setLed(3 - fruit[0] / 8, fruit[1], fruit[0] % 8, 1);

        pos_x[snake_size - 1] = last_x;
        pos_y[snake_size - 1] = last_y;

        //DISPLAY POINTS
        uint8_t pts = snake_size - 4;
        uint8_t p1 = pts / 10;
        uint8_t p2 = pts - p1 * 10;

        byte x[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        for (int i = 0; i < 5; i++)
        {
          x[i + 2] = (numbers[p1][i] << 4) + numbers[p2][i]; //
        }
        print_pattern(x, sizeof(x), 0);
      }

      if (dir == "left")
        pos_x[0] - 1 >= 0 ? pos_x[0] -= 1 : pos_x[0] = 23;
      else if (dir == "right")
        pos_x[0] + 1 <= 23 ? pos_x[0] += 1 : pos_x[0] = 0;
      else if (dir == "up")
        pos_y[0] - 1 >= 0 ? pos_y[0] -= 1 : pos_y[0] = 7;
      else if (dir == "down")
        pos_y[0] + 1 <= 7 ? pos_y[0] += 1 : pos_y[0] = 0;

      //UPDATE SNAKE HEAD
      lc.setLed(3 - pos_x[0] / 8, pos_y[0], pos_x[0] % 8, 1);

      //UPDATE LAST SNAKE PART
      lc.setLed(3 - pos_x[snake_size - 1] / 8, pos_y[snake_size - 1], pos_x[snake_size - 1] % 8, 0);

      //GAME END
      for (int i = 0; i < snake_size; i++)
      {
        for (int j = 0; j < i; j++)
        {
          if (pos_x[i] == pos_x[j] and pos_y[i] == pos_y[j])
            end_game = true;
        }
      }
    }

    uint8_t dir_cmd = 0;
    if (Serial.available())
      dir_cmd = Serial.read();

    if (dir_cmd == 114 and dir != "left")
      dir = "right";
    else if (dir_cmd == 108 and dir != "right")
      dir = "left";
    else if (dir_cmd == 117 and dir != "down")
      dir = "up";
    else if (dir_cmd == 100 and dir != "up")
      dir = "down";
    else if (dir_cmd == 113) //'q'
      return 0;
  }
  //WAIT 5SEC
  delay(5000);

  //CLEAR POINTS DISPLAY
  lc.clearDisplay(0);

  //NEW GAME
  snake();
}

void reset_mode()
{
  for (int i = 0; i < 4; i++)
  {
    if (matrixes[i])
      modes[i] = ' ';
  }
}

void clear()
{
  modes = "    ";
  for (int i = 0; i < 4; i++)
  {
    lc.clearDisplay(i);
    matrixes[i] = 0;
  }
}

void random_pattern()
{
  byte rand_num[8] = {byte(random(255)), byte(random(255)), byte(random(255)), byte(random(255)), byte(random(255)), byte(random(255)), byte(random(255)), byte(random(255))};

  for (int i = 0; i < 4; i++)
  {
    if (modes[i] == 'r')
      print_pattern(rand_num, sizeof(rand_num), i);
  }
  random_num_t = millis();
}

void display_text(String text, uint8_t index)
{
  text_t = millis();
  if (text_i > entered_text.length() + 2)
    text_i = 0;

  for (int i = 0; i < 4; i++)
  {
    lc.clearDisplay(i);
  }

  for (int i = 0; i <= 4; i++)
  {
    if (index - i >= 0)
    {
      if ((int)text[index - i] >= 65 and (int)text[index - i] <= 90) //LETTERS
        print_pattern(letters[(int)text[index - i] - 65], 7, i);
      else if ((int)text[index - i] >= 48 and (int)text[index - i] <= 57) //NUMBERS
        print_pattern(numbers_big[(int)text[index - i] - 48], 7, i);
    }
  }
  text_i++;
}
