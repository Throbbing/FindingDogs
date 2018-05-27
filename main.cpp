#include "EditorApp.h"
#include "GameApp.h"

#define Editor
#ifdef Editor
MAKE_APP(FDGameEditor)
#else
MAKE_APP(FDGame)
#endif