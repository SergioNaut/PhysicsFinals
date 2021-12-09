#pragma once
#include "extern_includes.h"
//TODO: por em um arquivo melhor
namespace nGeometry
{
    // Compute the 2D pseudo cross product Dot(Perp(u), v)
    float Cross2D(float uX, float uY, float vX, float vY)
    {
        return (uY * vX) - (uX * vY);
    }

    // Test if 2D point P lies inside the counterclockwise 2D triangle ABC
    bool PointInTriangle(float pX, float pY, float aX, float aY, float bX, float bY, float cX, float cY)
    {
        // If P to the right of AB then outside triangle
        if (Cross2D(pX - aX, pY - aY, bX - aX, bY - aY) < 0.0f) return false;
        // If P to the right of BC then outside triangle
        if (Cross2D(pX - bX, pY - bY, cX - bX, cY - bY) < 0.0f) return false;
        // If P to the right of CA then outside triangle
        if (Cross2D(pX - cX, pY - cY, aX - cX, aY - cY) < 0.0f) return false;
        // Otherwise P must be in (or on) the triangle
        return true;
    }

    glm::vec3 ClosestPtPointTriangle(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
    {
        // Check if P in vertex region outside A
        glm::vec3 ab = b - a;
        glm::vec3 ac = c - a;
        glm::vec3 ap = p - a;
        float d1 = glm::dot(ab, ap);
        float d2 = glm::dot(ac, ap);
        if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)

        // Check if P in vertex region outside B
        glm::vec3 bp = p - b;
        float d3 = glm::dot(ab, bp);
        float d4 = glm::dot(ac, bp);
        if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)

        // Check if P in edge region of AB, if so return projection of P onto AB
        float vc = d1 * d4 - d3 * d2;
        if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
            float v = d1 / (d1 - d3);
            return a + v * ab; // barycentric coordinates (1-v,v,0)
        }

        // Check if P in vertex region outside C
        glm::vec3 cp = p - c;
        float d5 = glm::dot(ab, cp);
        float d6 = glm::dot(ac, cp);
        if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)

        // Check if P in edge region of AC, if so return projection of P onto AC
        float vb = d5 * d2 - d1 * d6;
        if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
            float w = d2 / (d2 - d6);
            return a + w * ac; // barycentric coordinates (1-w,0,w)
        }

        // Check if P in edge region of BC, if so return projection of P onto BC
        float va = d3 * d6 - d5 * d4;
        if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
            float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
            return b + w * (c - b); // barycentric coordinates (0,1-w,w)
        }

        // P inside face region. Compute Q through its barycentric coordinates (u,v,w)
        float denom = 1.0f / (va + vb + vc);
        float v = vb * denom;
        float w = vc * denom;
        return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f - v - w
    }
}