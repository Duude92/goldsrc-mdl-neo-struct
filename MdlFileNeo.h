// HHD Software Hex Editor Neo
//structure Definition File
// Creation date: 03.05.2024 10:48:38
//
// Consult thestructure Viewer documentation for more information:
//
// *structure Viewer Overview: https://www.hhdsoftware.com/online-doc/hex/structure-viewer
// * Language Reference: https://www.hhdsoftware.com/online-doc/hex/language-reference

// Include standard type definitions
#include "stddefs.h"

#pragma byte_order(LittleEndian)

#pragma pack(1)


struct Vector3 {
	float x;
	float y;
	float z;
};

struct Bone {
	char BoneName[32];
	int parent;
	int flags;
	int bonecontroller[6];
	float value[6];
	float scale[6];
};

struct BoneController {
	int bone;
	int type;
	float start;
	float end;
	int rest;
	int index;
};

struct HitBox {
	int bone;
	int group;
	Vector3 bbmin;
	Vector3 bbmax;
};

struct SequenceGroup {
	char label[32];
	char name[64];
	int unused1;
	int unused2;
};

struct Sequence {
	char label[32];
	float fps;
	int flags;
	int activity;
	int actweight;
	int numevents;
	int eventindex;
	int numframes;
	int numpivots;
	int pivotindex;
	int motiontype;
	int motionbone;
	Vector3 linearmovement;
	int automoveposindex;
	int automoveangleindex;
	Vector3 bbmin;
	Vector3 bbmax;
	int numblends;
	int animindex;
	int blendtype[2];
	float blendstart[2];
	float blendend[2];
	int blendparent;
	int seqgroup;
	int entrynode;
	int exitnode;
	int nodeflags;
	int nextseq;
};


struct TextureData{
	unsigned char Data[width * height];
	unsigned char Palette[256 * 3];

};
struct TextureHeader{
	char name[64];
	int flags;
	int width;
	int height;
	int index;
};
public struct Texture {
	TextureHeader Header;
	TextureData Data;
};
struct Bodypart {
	char name[64];
	int nummodels;
	int base;
	int modelindex;
};

struct Mesh {
	int numtris;
	int triindex;
	int skinref;
	int numnorms;
	int normindex;
};

struct Model {
	char name[64];
	int type;
	float boundingradius;
	int nummesh;
	int meshindex;
	int numverts;
	int vertinfoindex;
	int vertindex;
	int numnorms;
	int norminfoindex;
	int normindex;
	int numgroups;
	int groupindex;
};

struct UV {
	short horizontal;
	short vertical;
};

struct TriVert {
	short vertindex;
	short normindex;
	UV UV;
};

struct TriSequence {
	short type;
	TriVert TriVerts[((type >> (2 * 8 - 1)) + type) ^ (type >> (2 * 8 - 1))];
};

struct Header {
	char IDS[4];
	int Version;
	char Filename[64];
	int Length;
	Vector3 EyePosition;
	Vector3 HullMin;
	Vector3 HullMax;
	Vector3 BBMin;
	Vector3 BBmax;
	int Flags;
	int BoneCount;
	int BoneIndex;
	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxes;
	int hitboxindex;
	int numseq;
	int seqindex;
	int numseqgroups;
	int seqgroupindex;
	int numtextures;
	int textureindex;
	int texturedataindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numattachments;
	int attachmentindex;
	int soundtable;
	int soundindex;
	int soundgroups;
	int soundgroupindex;
	int numtransitions;
	int transitionindex;
};
struct TriSequences{
	while(1)
	{
		TriSequence CurrentTriSequence;

		if(CurrentTriSequence.type== 0) break;
	}
};
public struct Textures{
	TextureHeader TextureHeaders[1];
	for(var i = 0; i<1; i=i+1)
	{
		struct TextureDataStruct{
			unsigned char Data[TextureHeaders[i].width * TextureHeaders[i].height];
			unsigned char Palette[256 * 3];
		};
		TextureDataStruct textureData;
	}
};
public struct MdlFile {
	Header Header;
	Bone Bones[Header.BoneCount];
	BoneController BoneControllers[Header.numbonecontrollers];
	HitBox HitBoxes[Header.numhitboxes];
	unsigned char Anim[24];
	Sequence sequences[Header.numseq];
	SequenceGroup SequenceGroups[Header.numseqgroups];
	Bodypart bodyparts[Header.numbodyparts];
	Model Model;
	unsigned char VertexBones[Model.numverts];
	unsigned char Normalbones[Model.numnorms];
	Vector3 Vertices[Model.numverts];
	Vector3 Normals[Model.numnorms];
	Mesh Meshs[Model.nummesh];
	// TriSequences SequencesTri;
	unsigned char TriSeq[Header.textureindex - Meshs[0].triindex];


	TextureHeader TextureHeaders[Header.numtextures];
	for (var i = 0; i < Header.numtextures; i = i + 1)
	{
		struct TextureDataStruct{
			unsigned char Data[TextureHeaders[i].width * TextureHeaders[i].height];
			unsigned char Palette[256 * 3];
		};
		TextureDataStruct textureData;
	}
};