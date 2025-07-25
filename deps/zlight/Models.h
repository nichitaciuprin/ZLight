#pragma once

#include "BaseMath.h"

const Vector3 ModelCubeVerteces[8] =
{
    { -0.5f, -0.5f, -0.5f },
    { -0.5f, -0.5f,  0.5f },
    { -0.5f,  0.5f, -0.5f },
    { -0.5f,  0.5f,  0.5f },
    {  0.5f, -0.5f, -0.5f },
    {  0.5f, -0.5f,  0.5f },
    {  0.5f,  0.5f, -0.5f },
    {  0.5f,  0.5f,  0.5f }
};
const int ModelCubeIndecesLine[12][2] =
{
    {0, 1},
    {1, 5},
    {5, 4},
    {4, 0},
    {2, 3},
    {3, 7},
    {7, 6},
    {6, 2},
    {0, 2},
    {1, 3},
    {5, 7},
    {4, 6}
};
const int ModelCubeIndecesTriangle[12][3] =
{
    {2, 6, 4},
    {4, 0, 2},
    {6, 7, 5},
    {5, 4, 6},
    {7, 3, 1},
    {1, 5, 7},
    {3, 2, 0},
    {0, 1, 3},
    {1, 0, 4},
    {4, 5, 1},
    {3, 7, 6},
    {6, 2, 3}
};
const int ModelCubeIndecesQuad[6][4] =
{
    {2, 6, 4, 0},
    {6, 7, 5, 4},
    {7, 3, 1, 5},
    {3, 2, 0, 1},
    {1, 0, 4, 5},
    {3, 7, 6, 2}
};

const Vector3 ModelSphereVerteces[32] =
{
    {  0.000000,  0.500000, -0.000000  },
    {  0.250000,  0.433000, -0.000000  },
    {  0.433000,  0.250000, -0.000000  },
    {  0.500000,  0.000000,  0.000000  },
    {  0.433000, -0.250000,  0.000000  },
    {  0.250000, -0.433000,  0.000000  },
    {  0.000000, -0.500000,  0.000000  },
    {  0.125000,  0.433000,  0.216500  },
    {  0.216500,  0.250000,  0.375000  },
    {  0.250000,  0.000000,  0.433000  },
    {  0.216500, -0.250000,  0.375000  },
    {  0.125000, -0.433000,  0.216500  },
    { -0.125000,  0.433000,  0.216500  },
    { -0.216500,  0.250000,  0.375000  },
    { -0.250000,  0.000000,  0.433000  },
    { -0.216500, -0.250000,  0.375000  },
    { -0.125000, -0.433000,  0.216500  },
    { -0.250000,  0.433000, -0.000000  },
    { -0.433000,  0.250000, -0.000000  },
    { -0.500000,  0.000000,  0.000000  },
    { -0.433000, -0.250000,  0.000000  },
    { -0.250000, -0.433000,  0.000000  },
    { -0.125000,  0.433000, -0.216500  },
    { -0.216500,  0.250000, -0.375000  },
    { -0.250000, -0.000000, -0.433000  },
    { -0.216500, -0.250000, -0.375000  },
    { -0.125000, -0.433000, -0.216500  },
    {  0.125000,  0.433000, -0.216500  },
    {  0.216500,  0.250000, -0.375000  },
    {  0.250000, -0.000000, -0.433000  },
    {  0.216500, -0.250000, -0.375000  },
    {  0.125000, -0.433000, -0.216500  }
};
const int ModelSphereIndecesTriangles[60][3] =
{
    {0, 7, 1},
    {1, 7, 8},
    {1, 8, 2},
    {2, 8, 9},
    {2, 9, 3},
    {3, 9, 10},
    {3, 10, 4},
    {4, 10, 11},
    {4, 11, 5},
    {5, 11, 6},
    {0, 12, 7},
    {7, 12, 13},
    {7, 13, 8},
    {8, 13, 14},
    {8, 14, 9},
    {9, 14, 15},
    {9, 15, 10},
    {10, 15, 16},
    {10, 16, 11},
    {11, 16, 6},
    {0, 17, 12},
    {12, 17, 18},
    {13, 18, 19},
    {14, 19, 20},
    {15, 20, 21},
    {12, 18, 13},
    {13, 19, 14},
    {14, 20, 15},
    {15, 21, 16},
    {16, 21, 6},
    {0, 22, 17},
    {17, 22, 23},
    {18, 23, 24},
    {19, 24, 25},
    {20, 25, 26},
    {17, 23, 18},
    {18, 24, 19},
    {19, 25, 20},
    {20, 26, 21},
    {21, 26, 6},
    {0, 27, 22},
    {22, 27, 28},
    {23, 28, 29},
    {24, 29, 30},
    {25, 30, 31},
    {22, 28, 23},
    {23, 29, 24},
    {24, 30, 25},
    {25, 31, 26},
    {26, 31, 6},
    {0, 1, 27},
    {27, 1, 2},
    {28, 2, 3},
    {29, 3, 4},
    {30, 4, 5},
    {27, 2, 28},
    {28, 3, 29},
    {29, 4, 30},
    {30, 5, 31},
    {31, 5, 6},
};
