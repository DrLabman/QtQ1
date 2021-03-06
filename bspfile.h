#ifndef BSPFILE_H
#define BSPFILE_H

#include "basictypes.h"

typedef struct                 // Bounding Box, Float values
{
    Vec3   min;                // minimum values of X,Y,Z
    Vec3   max;                // maximum values of X,Y,Z
} BoundBox;

typedef struct                 // Bounding Box, Short values
{
    short  min;                 // minimum values of X,Y,Z
    short  max;                 // maximum values of X,Y,Z
} BBoxShort;

struct BSPEntry
{
    /** Offset to this entry, in bytes, from the start of the file. */
    int offset;
    /** Size of this entry in bytes. */
    int size;
};

struct BSPEdge
{
    unsigned short vertex1;
    unsigned short vertex2;
};

#define	MAX_LIGHTMAPS	4

struct BSPFace
{
    short planeNumber;
    short side;
    int   firstEdge;
    short countOfEdges;
    short textureInfo;

// lighting info
    unsigned char styles[MAX_LIGHTMAPS];
    int           lightOffset;		// start of [numstyles*surfsize] samples

    short getEdge(int edge);
};

struct BSPTextureInfo
{
    Vec3   vectorS;            // S vector, horizontal in texture space)
    scalar distS;              // horizontal offset in texture space
    Vec3   vectorT;            // T vector, vertical in texture space
    scalar distT;              // vertical offset in texture space
    int   textureId;          // Index of MipTexExtries
    int   animated;           // 0 for ordinary textures, 1 for water
};

#define	MIPLEVELS	4
struct BSPMipTex {
    char		name[16];
    unsigned	width;
    unsigned    height;
    unsigned	offsets[MIPLEVELS];		// four mip maps stored
};

struct BSPMipTexEntries {
    int			numMipTex;
    int			dataofs[];          // [nummiptex]
};

#define	MAX_MAP_HULLS 4

struct BSPModel
{
    BoundBox    bounds;
    Vec3		origin;
    int			headnode[MAX_MAP_HULLS];
    int			numLeaves;		// number of BSP leaves
    int			faceId;
    int         numFaces;
};

struct BSPFile
{
    /** BSP File Version number. */
    int  version;               // Model version, must be 0x17 (23).
    /** List of Entities. */
    BSPEntry entities;
    /** Planes: numplanes = size/sizeof(plane_t) */
    BSPEntry planes;
    /** Textures. */
    BSPEntry miptex;
    /** Vertices:  numvertices = size/sizeof(vertex_t) */
    BSPEntry vertices;
    /** Visibility lists. */
    BSPEntry visilist;
    /** BSP Nodes: numnodes = size/sizeof(node_t) */
    BSPEntry nodes;
    /** Surface Texture Information: numtexinfo = size/sizeof(texinfo_t) */
    BSPEntry texinfo;
    /** Surface Faces: numfaces = size/sizeof(face_t) */
    BSPEntry faces;
    /** Lightmaps. */
    BSPEntry lightmaps;
    /** Clipnodes: numclips = size/sizeof(clipnode_t) */
    BSPEntry clipnodes;
    /** BSP Leaves: numlaves = size/sizeof(leaf_t) */
    BSPEntry leaves;
    /** List of faces. */
    BSPEntry listOfFaces;
    /** Edges: numedges = Size/sizeof(edge_t) */
    BSPEntry edges;
    /** List of edges. */
    BSPEntry listOfEdges;
    /** Sub-Models: List of Models: nummodels = Size/sizeof(model_t) */
    BSPEntry models;

    /** Checks the version number of this file vs the list of versions we support. */
    bool isSupportedFile();

    BSPModel *getModels();
    int countOfModels();

    char *getEntities();
    int entityStringSize();

    Vec3 *getVertices();
    int countOfVertices();

    BSPEdge *getEdges();
    int countOfEdges();

    BSPFace *getFaces();
    int countOfFaces();

    BSPTextureInfo *getTextureInfos();
    int countOfTextureInfos();
    
    int *getEdgeList();

    BSPMipTexEntries *getTexturesEntries();
    BSPMipTex *getMipTexture(int texture);
};

#endif // BSPFILE_H
