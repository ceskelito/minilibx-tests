# MLXLib - Comprehensive MinilibX Wrapper

Una libreria completa che semplifica l'utilizzo di MinilibX fornendo strutture unificate, gestione degli eventi, funzioni per i gradienti e utilities per il disegno.

## Panoramica

MLXLib è una sovrastruttura alla libreria MinilibX che raggruppa e semplifica:

- **Gestione delle istanze MLX**: Strutture unificate per istanze, finestre e immagini
- **Sistema di eventi**: Handlers per eventi comuni (tasti, mouse, chiusura finestre)
- **Gestione colori avanzata**: Funzioni per gradienti, blending e manipolazione colori
- **Utilities per il disegno**: Forme di base, forme con gradiente
- **Gestione memoria automatica**: Cleanup automatico delle risorse

## Struttura del Progetto

```
my_libraries/
├── colors/          # Gestione colori e definizioni
├── imglib/          # Gestione immagini base
└── mlxlib/          # Wrapper completo MLX
```

## Componenti

### 1. Colors Library

**File**: `colors/colors.h`, `colors/colors.c`, `colors/colorsdef.h`

Fornisce:
- Manipolazione colori TRGB
- Oltre 100 colori predefiniti
- Funzioni per blending, inversione, scala di grigi
- Controllo trasparenza e luminosità

```c
#include "colors.h"

// Creazione colori
int color = clr_create_rgb(255, 128, 64);
int transparent = clr_add_transparency(color, 128);

// Manipolazione
int inverted = clr_invert(color);
int gray = clr_grayscale(color);
int bright = clr_adjust_brightness(color, 1.5f);

// Blending
int mixed = clr_blend(COLOR_RED, COLOR_BLUE, 0.5f);
```

### 2. ImgLib Library

**File**: `imglib/imglib.h`, `imglib/imglib.c`

Fornisce:
- Struttura `t_data_img` per gestione immagini
- Funzioni sicure per pixel manipulation
- Gestione offset e indirizzamento memoria

```c
#include "imglib.h"

t_data_img img;
img_create(mlx_ptr, &img, 800, 600);
img_put_pixel(&img, 100, 100, COLOR_RED);
```

### 3. MLXLib Wrapper (Core)

**File**: `mlxlib/mlxlib.h`, `mlxlib/*.c`

#### Strutture Principali

```c
// Istanza MLX principale
typedef struct s_mlx_instance
{
    void            *mlx_ptr;        // Puntatore MLX
    t_mlx_window    *windows;        // Lista finestre
    int             num_windows;     // Numero finestre
    // Event handlers globali
    // Gestione stato applicazione
} t_mlx_instance;

// Finestra MLX
typedef struct s_mlx_window
{
    void            *win_ptr;        // Puntatore finestra MLX
    char            *title;          // Titolo finestra
    int             width, height;   // Dimensioni
    t_data_img      **images;        // Array immagini
    // Event handlers specifici finestra
    // Dati utente
} t_mlx_window;
```

#### API Principale

**Inizializzazione e gestione istanza:**
```c
t_mlx_instance *mlxlib_init(void);
int mlxlib_destroy(t_mlx_instance *instance);
int mlxlib_loop(t_mlx_instance *instance);
int mlxlib_loop_end(t_mlx_instance *instance);
```

**Gestione finestre:**
```c
t_mlx_window *mlxlib_new_window(t_mlx_instance *instance, int width, int height, char *title);
int mlxlib_destroy_window(t_mlx_window *window);
int mlxlib_clear_window(t_mlx_window *window);
```

**Gestione immagini:**
```c
t_data_img *mlxlib_new_image(t_mlx_window *window, int width, int height);
int mlxlib_destroy_image(t_mlx_window *window, t_data_img *image);
int mlxlib_put_image(t_mlx_window *window, t_data_img *image, int x, int y);
```

#### Sistema Eventi

**Event Handlers:**
```c
// Tipi di handler
typedef int (*t_key_handler)(int keycode, void *param);
typedef int (*t_mouse_handler)(int button, int x, int y, void *param);
typedef int (*t_close_handler)(void *param);

// Impostazione handlers
int mlxlib_set_key_handler(t_mlx_window *window, t_key_handler handler, int event_type);
int mlxlib_set_mouse_handler(t_mlx_window *window, t_mouse_handler handler, int event_type);
int mlxlib_set_close_handler(t_mlx_window *window, t_close_handler handler);
```

**Eventi supportati:**
- `MLXLIB_KEY_PRESS` / `MLXLIB_KEY_RELEASE`: Pressione/rilascio tasti
- `MLXLIB_MOUSE_PRESS` / `MLXLIB_MOUSE_RELEASE`: Click mouse
- `MLXLIB_MOUSE_MOVE`: Movimento mouse
- Chiusura finestra automatica

#### Funzioni Gradienti

```c
// Creazione gradiente
t_gradient *mlxlib_create_gradient(int start_color, int end_color, int steps);

// Calcolo colore a posizione specifica (0.0 - 1.0)
int mlxlib_gradient_color(t_gradient *grad, float position);

// Disegno con gradiente
void mlxlib_draw_gradient_rectangle(t_data_img *img, int x, int y, int width, int height, t_gradient *grad, int direction);
void mlxlib_draw_gradient_circle(t_data_img *img, int center_x, int center_y, int radius, t_gradient *grad);
```

#### Utilities Disegno

```c
// Forme base
void mlxlib_draw_line(t_data_img *img, int start[2], int end[2], int color);
void mlxlib_draw_rectangle(t_data_img *img, int x, int y, int width, int height, int color);
void mlxlib_fill_rectangle(t_data_img *img, int x, int y, int width, int height, int color);
void mlxlib_draw_circle(t_data_img *img, int center_x, int center_y, int radius, int color);
void mlxlib_fill_circle(t_data_img *img, int center_x, int center_y, int radius, int color);

// Operazioni pixel sicure
int mlxlib_put_pixel_safe(t_data_img *img, int x, int y, int color);
int mlxlib_get_pixel(t_data_img *img, int x, int y);
```

#### Funzioni Colore Avanzate

```c
// Blending e interpolazione
int mlxlib_blend_colors(int color1, int color2, float ratio);
int mlxlib_interpolate_rgb(int start_r, int start_g, int start_b, int end_r, int end_g, int end_b, float ratio);

// Spazio colore HSV
int mlxlib_hsv_to_rgb(float h, float s, float v);
void mlxlib_rgb_to_hsv(int rgb, float *h, float *s, float *v);

// Manipolazione luminosità
int mlxlib_lighten_color(int color, float factor);
int mlxlib_darken_color(int color, float factor);
```

## Esempio Completo

Vedi `examples/comprehensive_example.c` per un esempio completo che dimostra:

- Inizializzazione istanza MLX
- Creazione finestra con event handlers
- Gestione eventi tastiera e mouse
- Disegno con gradienti
- Gestione chiusura finestra
- Cleanup automatico risorse

### Controlli Esempio

- **ESC**: Uscita
- **Spazio**: Pulisce canvas
- **1**: Modalità cerchio
- **2**: Modalità cerchio con gradiente
- **3**: Modalità rettangolo
- **Click sinistro**: Disegna in base alla modalità
- **Pulsante chiusura**: Uscita pulita

## Build

```bash
# Build di tutte le librerie
cd my_libraries/colors && make
cd ../imglib && make
cd ../mlxlib && make

# Build esempio
cd ../examples && make
```

## Vantaggi della Libreria

1. **Gestione Unificata**: Un'unica struttura per gestire istanze MLX, finestre e immagini
2. **Event System Robusto**: Handlers automatici per eventi comuni
3. **Gestione Memoria**: Cleanup automatico delle risorse
4. **Colori Avanzati**: Sistema completo per gradienti e manipolazione colori
5. **Drawing Utilities**: Forme di base e avanzate
6. **Sicurezza**: Controlli bounds e gestione errori
7. **Modularità**: Librerie separate riutilizzabili
8. **Facilità d'uso**: API intuitiva che nasconde la complessità di MLX

## Struttura File

```
minilibx-tests/
├── my_libraries/
│   ├── colors/
│   │   ├── colors.h          # Header funzioni colori
│   │   ├── colorsdef.h       # Definizioni colori predefiniti
│   │   ├── colors.c          # Implementazione
│   │   └── Makefile
│   ├── imglib/
│   │   ├── imglib.h          # Header gestione immagini
│   │   ├── imglib.c          # Implementazione
│   │   └── Makefile
│   └── mlxlib/
│       ├── mlxlib.h          # Header principale wrapper
│       ├── mlxlib_core.c     # Gestione istanze e finestre
│       ├── mlxlib_events.c   # Sistema eventi
│       ├── mlxlib_colors.c   # Funzioni colori avanzate
│       ├── mlxlib_drawing.c  # Utilities disegno
│       └── Makefile
├── examples/
│   ├── comprehensive_example.c  # Esempio completo
│   └── Makefile
├── variables.mk              # Variabili build comuni
└── README_MLXLIB.md         # Questa documentazione
```

Questa libreria fornisce tutto il necessario per utilizzare MinilibX in modo semplice ed efficace, con gestione automatica delle risorse e un'API intuitiva per tutte le operazioni comuni.