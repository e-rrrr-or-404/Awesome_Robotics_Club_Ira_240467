
## Part A: Detecting Which Piece Moves From Which Square to Which

### Objective
To determine the movement of chess pieces (from which square to which, and which specific piece) **without using computer vision, RFID, or magnetic sensors**. The proposed solution uses **capacitive sensing combined with passive profiling** of chess pieces.

---

## 1. Technologies Used

### 1.1 Capacitive Sensing
Capacitive sensors measure the change in capacitance when a conductive or dielectric object is present. Each square on the board acts as a capacitive pad.

- Detects when a piece is **lifted** (capacitance drop - ACTIVATION)
- Detects when a piece is **placed** (capacitance rise - PLACEMENT)

**Why capacitive?**
- Inexpensive
- Non-mechanical
- Highly scalable
- No line-of-sight needed (unlike vision or other light based solutions)

**Materials**
- for capacitive sensors - Copper (highly conductive, widely available, durable) or Aluminium (more cost-effective, little loss in conductivity)
- for dielectric (insulating layer) - Glass or Plastic (more durable)
- for shielding material (insulating) - soft foam
- for chess pieces - layer of conductive graphite or conductive paint for capacitive signature

### 1.2 Profiling of Pieces
Each chess piece is designed to have a **unique capacitive signature**, based on:
- Contact area at base
- Material used - Which conductive paint is used
- (cost intensive alternative that is not discussed here - embedded capacitors)

When a piece is placed on a square, it alters the square's capacitance in a predictable way.

---

## 2. System Design

### 2.1 Board Layout

Capacitive Sensor Array:

-Each of the 64 squares on the chessboard will be equipped with a capacitive sensor. These sensors will be designed as copper electrodes placed beneath each square.

-Electrode Grid: The chessboard can be divided into a matrix of rows and columns, where each intersection of the grid corresponds to one of the 64 squares.

-Capacitive Detection: When a chess piece is placed on or removed from a square, it will change the local capacitance of that square's sensor, triggering a signal.

- 8 rows and 8 columns = 16 I/O lines

### 2.2 Piece Profiling
Pieces have varying capacitive footprints. For example:

| Piece   | Capacitance Range |
|---------|-------------------|
| Pawn    | 100–150 pF        |
| Knight  | 180–230 pF        |
| Bishop  | 250–300 pF        |
| Rook    | 320–370 pF        |
| Queen   | 390–450 pF        |
| King    | 470–550 pF        |

Pieces may use materials like:
- Conductive foil
- Graphite
- Embedded metal discs

---

## 3. Detection Process

### Step-by-Step Workflow
1. **Scan baseline**: Read capacitance of all 64 squares. 
2. **Detect activation**: When a piece is lifted, capacitance drops below threshold.
3. **Detect placement**: When a piece is placed, capacitance increases.
4. **Identify piece**: Measure the final capacitance and match with a lookup table such as the sample given obove


### Logic Example (Simplified)
```cpp
int identifyPiece(int cap) {
  if (cap < 150) return PAWN;
  else if (cap < 230) return KNIGHT;
  else if (cap < 300) return BISHOP;
  else if (cap < 370) return ROOK;
  else if (cap < 450) return QUEEN;
  else return KING;
}
```

---

## 4. Practical Outcomes

### Advantages
- No computer vision, RFID, or magnets required
- Robust to lighting and physical misalignment
- Easy to manufacture with low-cost materials

### Limitations & Solutions
| Issue               | Cause                    | Solution                             |
|---------------------|--------------------------|--------------------------------------|
| Noisy readings      | Electrical interference  | Add shielding (foam) , use filters   |
| Similar signatures  | Poor design margins      | Widen signature gaps                 |
| Human interference  | Capacitance from fingers | Add debounce/delay logic. for eg, only if activation and placement are within a defined time period, should the system record move|
| Environmental drift | Temp/humidity changes    | Auto-calibrate baseline periodically |

---

## Part B: Reducing Pin Count for 64 Inputs

### Problem
Arduino has only ~20 I/O pins, but the board has 64 inputs (one per square).

### Solution: Matrix Scanning

- Arrange squares in an **8x8 grid**: rows and columns
- Each square connects to one row and one column
- controller scans one row at a time and read the columns

This reduces the pin requirement from 64 to **16 pins** (8 rows + 8 columns).

### Optional Enhancements
- Use **multiplexers**

#### sample multiplexer - CD74HC4067
- A multiplexer (MUX) is a digital switch that selects one input from many and forwards it to a single output line, based on selector (address) inputs.
- For example, a 16-channel analog multiplexer like the CD74HC4067 has:

    16 I/O channels (S0–S15)

    4 selector pins (A0–A3)

    1 common signal pin (SIG)

- By setting the selector pins to a binary value, you choose which channel is connected to the SIG pin.

|Select Inputs (A3 A2 A1 A0) | Connected Channel|
|----------------------------|------------------|
|0000                        | S0               |
|0001                        | S1               |
|...                         | ...              |
|1111                        | S15              |

-divide our 16 total lines (8 rows + 8 columns) into two sets of 8, and use one 16:1 multiplexer for each set:

    MUX 1 handles all 8 rows

    MUX 2 handles all 8 columns

-Both multiplexers share the same 4 selector pins, and each has its own signal line (connected to a microcontroller input).

-Instead of directly connecting 16 I/O pins to your microcontroller, this approach uses only:

    4 pins for selector lines (shared)

    1 pin for row signal

    1 pin for column signal

Total: 6 microcontroller pins

---

Arduino Pseudo-Code:

int baseValues[8][8];      
int currentValues[8][8];   

void scanBoard() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      currentValues[row][col] = readCapacitance(row, col);  // Read from pad
    }
  }
}

void detectMove() {
  int fromSquare[2] = {-1, -1};
  int toSquare[2] = {-1, -1};

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      int delta = currentValues[row][col] - baseValues[row][col];

      if (delta < -THRESHOLD) {
        fromSquare[0] = row;
        fromSquare[1] = col;
      } else if (delta > THRESHOLD) {
        toSquare[0] = row;
        toSquare[1] = col;
      }
    }
  }

  if (fromSquare[0] != -1 && toSquare[0] != -1) {
    Serial.print("Move detected: ");
    Serial.print((char)('A' + fromSquare[1])); Serial.print(8 - fromSquare[0]);
    Serial.print(" → ");
    Serial.print((char)('A' + toSquare[1])); Serial.println(8 - toSquare[0]);
  }
}



