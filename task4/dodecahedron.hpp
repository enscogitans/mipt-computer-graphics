#pragma once

#include <GL/glew.h>


namespace dodecahedron {

const GLfloat kTriangles[] = {
        // Face 1
        1.000f, 1.000f, 1.000f,
        1.618f, 0.000f, 0.618f,
        1.000f, -1.000f, 1.000f,

        1.000f, 1.000f, 1.000f,
        1.000f, -1.000f, 1.000f,
        0.000f, -0.618f, 1.618f,

        1.000f, 1.000f, 1.000f,
        0.000f, -0.618f, 1.618f,
        0.000f, 0.618f, 1.618f,

        // Face 2
        1.000f, 1.000f, 1.000f,
        0.000f, 0.618f, 1.618f,
        -1.000f, 1.000f, 1.000f,

        1.000f, 1.000f, 1.000f,
        -1.000f, 1.000f, 1.000f,
        -0.618f, 1.618f, 0.000f,

        1.000f, 1.000f, 1.000f,
        -0.618f, 1.618f, 0.000f,
        0.618f, 1.618f, 0.000f,

        // Face 3
        1.618f, 0.000f, 0.618f,
        1.618f, 0.000f, -0.618f,
        1.000f, 1.000f, -1.000f,

        1.618f, 0.000f, 0.618f,
        1.000f, 1.000f, -1.000f,
        0.618f, 1.618f, 0.000f,

        1.618f, 0.000f, 0.618f,
        0.618f, 1.618f, 0.000f,
        1.000f, 1.000f, 1.000f,

        // Face 4
        1.000f, 1.000f, -1.000f,
        0.000f, 0.618f, -1.618f,
        0.000f, -0.618f, -1.618f,

        1.000f, 1.000f, -1.000f,
        0.000f, -0.618f, -1.618f,
        1.000f, -1.000f, -1.000f,

        1.000f, 1.000f, -1.000f,
        1.000f, -1.000f, -1.000f,
        1.618f, 0.000f, -0.618f,

        // Face 5
        1.000f, 1.000f, -1.000f,
        0.618f, 1.618f, 0.000f,
        -0.618f, 1.618f, 0.000f,

        1.000f, 1.000f, -1.000f,
        -0.618f, 1.618f, 0.000f,
        -1.000f, 1.000f, -1.000f,

        1.000f, 1.000f, -1.000f,
        -1.000f, 1.000f, -1.000f,
        0.000f, 0.618f, -1.618f,

        // Face 6
        1.000f, -1.000f, 1.000f,
        0.618f, -1.618f, 0.000f,
        -0.618f, -1.618f, 0.000f,

        1.000f, -1.000f, 1.000f,
        -0.618f, -1.618f, 0.000f,
        -1.000f, -1.000f, 1.000f,

        1.000f, -1.000f, 1.000f,
        -1.000f, -1.000f, 1.000f,
        0.000f, -0.618f, 1.618f,

        // Face 7
        0.618f, -1.618f, 0.000f,
        1.000f, -1.000f, -1.000f,
        1.618f, 0.000f, -0.618f,

        0.618f, -1.618f, 0.000f,
        1.618f, 0.000f, -0.618f,
        1.618f, 0.000f, 0.618f,

        0.618f, -1.618f, 0.000f,
        1.618f, 0.000f, 0.618f,
        1.000f, -1.000f, 1.000f,

        // Face 8
        1.000f, -1.000f, -1.000f,
        0.000f, -0.618f, -1.618f,
        -1.000f, -1.000f, -1.000f,

        1.000f, -1.000f, -1.000f,
        -1.000f, -1.000f, -1.000f,
        -0.618f, -1.618f, 0.000f,

        1.000f, -1.000f, -1.000f,
        -0.618f, -1.618f, 0.000f,
        0.618f, -1.618f, 0.000f,

        // Face 9
        -1.000f, 1.000f, 1.000f,
        0.000f, 0.618f, 1.618f,
        0.000f, -0.618f, 1.618f,

        -1.000f, 1.000f, 1.000f,
        0.000f, -0.618f, 1.618f,
        -1.000f, -1.000f, 1.000f,

        -1.000f, 1.000f, 1.000f,
        -1.000f, -1.000f, 1.000f,
        -1.618f, 0.000f, 0.618f,

        // Face 10
        -0.618f, 1.618f, 0.000f,
        -1.000f, 1.000f, -1.000f,
        -1.618f, 0.000f, -0.618f,

        -0.618f, 1.618f, 0.000f,
        -1.618f, 0.000f, -0.618f,
        -1.618f, 0.000f, 0.618f,

        -0.618f, 1.618f, 0.000f,
        -1.618f, 0.000f, 0.618f,
        -1.000f, 1.000f, 1.000f,

        // Face 11
        -1.000f, 1.000f, -1.000f,
        -1.618f, 0.000f, -0.618f,
        -1.000f, -1.000f, -1.000f,

        -1.000f, 1.000f, -1.000f,
        -1.000f, -1.000f, -1.000f,
        0.000f, -0.618f, -1.618f,

        -1.000f, 1.000f, -1.000f,
        0.000f, -0.618f, -1.618f,
        0.000f, 0.618f, -1.618f,

        // Face 12
        -0.618f, -1.618f, 0.000f,
        -1.000f, -1.000f, -1.000f,
        -1.618f, 0.000f, -0.618f,

        -0.618f, -1.618f, 0.000f,
        -1.618f, 0.000f, -0.618f,
        -1.618f, 0.000f, 0.618f,

        -0.618f, -1.618f, 0.000f,
        -1.618f, 0.000f, 0.618f,
        -1.000f, -1.000f, 1.000f,
};

const GLfloat kColors[] = {
        // Face 1
        0.991f, 0.318f, 0.375f,
        0.991f, 0.318f, 0.375f,
        0.991f, 0.318f, 0.375f,

        0.991f, 0.318f, 0.375f,
        0.991f, 0.318f, 0.375f,
        0.991f, 0.318f, 0.375f,

        0.991f, 0.318f, 0.375f,
        0.991f, 0.318f, 0.375f,
        0.991f, 0.318f, 0.375f,

        // Face 2
        0.975f, 0.471f, 0.087f,
        0.975f, 0.471f, 0.087f,
        0.975f, 0.471f, 0.087f,

        0.975f, 0.471f, 0.087f,
        0.975f, 0.471f, 0.087f,
        0.975f, 0.471f, 0.087f,

        0.975f, 0.471f, 0.087f,
        0.975f, 0.471f, 0.087f,
        0.975f, 0.471f, 0.087f,

        // Face 3
        1.000f, 0.255f, 1.000f,
        1.000f, 0.255f, 1.000f,
        1.000f, 0.255f, 1.000f,

        1.000f, 0.255f, 1.000f,
        1.000f, 0.255f, 1.000f,
        1.000f, 0.255f, 1.000f,

        1.000f, 0.255f, 1.000f,
        1.000f, 0.255f, 1.000f,
        1.000f, 0.255f, 1.000f,

        // Face 4
        1.000f, 0.269f, 0.807f,
        1.000f, 0.269f, 0.807f,
        1.000f, 0.269f, 0.807f,

        1.000f, 0.269f, 0.807f,
        1.000f, 0.269f, 0.807f,
        1.000f, 0.269f, 0.807f,

        1.000f, 0.269f, 0.807f,
        1.000f, 0.269f, 0.807f,
        1.000f, 0.269f, 0.807f,

        // Face 5
        0.536f, 0.185f, 0.285f,
        0.536f, 0.185f, 0.285f,
        0.536f, 0.185f, 0.285f,

        0.536f, 0.185f, 0.285f,
        0.536f, 0.185f, 0.285f,
        0.536f, 0.185f, 0.285f,

        0.536f, 0.185f, 0.285f,
        0.536f, 0.185f, 0.285f,
        0.536f, 0.185f, 0.285f,

        // Face 6
        0.526f, 0.307f, 0.863f,
        0.526f, 0.307f, 0.863f,
        0.526f, 0.307f, 0.863f,

        0.526f, 0.307f, 0.863f,
        0.526f, 0.307f, 0.863f,
        0.526f, 0.307f, 0.863f,

        0.526f, 0.307f, 0.863f,
        0.526f, 0.307f, 0.863f,
        0.526f, 0.307f, 0.863f,

        // Face 7
        0.750f, 0.507f, 0.201f,
        0.750f, 0.507f, 0.201f,
        0.750f, 0.507f, 0.201f,

        0.750f, 0.507f, 0.201f,
        0.750f, 0.507f, 0.201f,
        0.750f, 0.507f, 0.201f,

        0.750f, 0.507f, 0.201f,
        0.750f, 0.507f, 0.201f,
        0.750f, 0.507f, 0.201f,

        // Face 8
        0.893f, 0.421f, 0.156f,
        0.893f, 0.421f, 0.156f,
        0.893f, 0.421f, 0.156f,

        0.893f, 0.421f, 0.156f,
        0.893f, 0.421f, 0.156f,
        0.893f, 0.421f, 0.156f,

        0.893f, 0.421f, 0.156f,
        0.893f, 0.421f, 0.156f,
        0.893f, 0.421f, 0.156f,

        // Face 9
        0.655f, 0.389f, 0.521f,
        0.655f, 0.389f, 0.521f,
        0.655f, 0.389f, 0.521f,

        0.655f, 0.389f, 0.521f,
        0.655f, 0.389f, 0.521f,
        0.655f, 0.389f, 0.521f,

        0.655f, 0.389f, 0.521f,
        0.655f, 0.389f, 0.521f,
        0.655f, 0.389f, 0.521f,

        // Face 10
        0.619f, 0.690f, 0.416f,
        0.619f, 0.690f, 0.416f,
        0.619f, 0.690f, 0.416f,

        0.619f, 0.690f, 0.416f,
        0.619f, 0.690f, 0.416f,
        0.619f, 0.690f, 0.416f,

        0.619f, 0.690f, 0.416f,
        0.619f, 0.690f, 0.416f,
        0.619f, 0.690f, 0.416f,

        // Face 11
        0.685f, 0.671f, 1.000f,
        0.685f, 0.671f, 1.000f,
        0.685f, 0.671f, 1.000f,

        0.685f, 0.671f, 1.000f,
        0.685f, 0.671f, 1.000f,
        0.685f, 0.671f, 1.000f,

        0.685f, 0.671f, 1.000f,
        0.685f, 0.671f, 1.000f,
        0.685f, 0.671f, 1.000f,

        // Face 12
        1.000f, 0.198f, 0.688f,
        1.000f, 0.198f, 0.688f,
        1.000f, 0.198f, 0.688f,

        1.000f, 0.198f, 0.688f,
        1.000f, 0.198f, 0.688f,
        1.000f, 0.198f, 0.688f,

        1.000f, 0.198f, 0.688f,
        1.000f, 0.198f, 0.688f,
        1.000f, 0.198f, 0.688f,
};

static_assert(sizeof(kTriangles) == sizeof(kColors), "Array sizes must be equal");

}  // namespace geometry
