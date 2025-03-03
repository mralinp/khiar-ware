# KhiarWare (Windows Version)

## Game Modification Tool for CS:GO

### Features: WallHack + TriggerBot + RadarHack + AutoBhop

⚠️ **IMPORTANT WARNING**: This project is for educational purposes only to demonstrate game security concepts. Using cheats in online games can result in permanent bans. The author is not responsible for any misuse of this code.

![menu image](demo.png)

## Setup Instructions

### Prerequisites

- Python 3 with `requests` library
- Visual Studio (configured for C++ development)
- CS:GO installed through Steam

### Installation

1. Clone the repository:

```bash
git clone https://github.com/mralinp/KhiarWare.git
```

2. Install Python dependencies:

```bash
pip install requests
```

3. Update offset values:

```bash
python updater.py
```

4. Build the project:

- Open `khiar-ware/khiar-ware.sln` in Visual Studio
- Ensure the build configuration is set to **x86** (32-bit)
- Build the solution

## Safe Testing (Recommended)

To safely test the code without risking a VAC ban, use CS:GO's insecure mode:

1. Open Steam
2. Right-click CS:GO in your library
3. Select Properties
4. Under "Launch Options", add `-insecure`
5. Click OK

In insecure mode:

- VAC will be disabled
- You cannot join VAC-secured servers
- Perfect for testing and development

To return to normal play:

- Remove `-insecure` from launch options
- Restart CS:GO

⚠️ **VAC Ban Warning**: Using this code on VAC-secured servers will likely result in a permanent game ban. The author takes no responsibility for banned accounts.

## Current Status

**Note**: Due to frequent CS:GO updates, some features may need adjustment to work with the latest game version. This code serves primarily as an educational reference for game security concepts.
