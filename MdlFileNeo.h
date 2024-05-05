//-
// Copyright (c) 2010 Yurii Hladyshenko
// https://github.com/Duude92/goldsrc-mdl-neo-struct
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// These definitions are based on:
// - The public specification of the MDL format within Open Asset Import Library Repository
//   See: https://github.com/malortie/assimp/wiki/MDL:-Half-Life-1-file-format
// - The Sledge editor repository
//	 See: https://github.com/LogicAndTrick/sledge/blob/master/Sledge.Providers/Model/Mdl10/Format/MdlFile.cs

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

struct TextureData {
  unsigned char Data[width * height];
  unsigned char Palette[256 * 3];
};
struct TextureHeader {
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
  if (type == 0)
    $break_array(true);
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

struct Attachment {
  char name[32];
  int type;
  int bone;
  Vector3 org;
  Vector3 vectors[3];
};
public struct Textures {
  TextureHeader TextureHeaders[1];
  for (var i = 0; i < 1; i = i + 1) {
    struct TextureDataStruct {
      unsigned char Data[TextureHeaders[i].width * TextureHeaders[i].height];
      unsigned char Palette[256 * 3];
    };
    TextureDataStruct textureData;
  }
};
struct Anim {
  unsigned char data[24];
};
public struct MdlFile {
  Header Header;
  Bone Bones[Header.BoneCount];
  BoneController BoneControllers[Header.numbonecontrollers];
  Attachment attachments[Header.numattachments];
  HitBox HitBoxes[Header.numhitboxes];
  var offset_backup = current_offset;

  $shift_by(Header.seqindex - offset_backup);
  Sequence sequences[Header.numseq];
  var offset_sequences = current_offset;

  $shift_by(offset_backup - current_offset);
  struct Animations {
    for (var i = 0; i < Header.numseq; i = i + 1) {
      Anim animation[Header.numseq];
    }
  };
  Animations animations;
  $shift_by(offset_sequences - current_offset);
  SequenceGroup SequenceGroups[Header.numseqgroups];
  Bodypart bodyparts[Header.numbodyparts];
  var modelCount = 0;
  for (var i = 0; i < Header.numbodyparts; i = i + 1) {
    Model Models[bodyparts[i].nummodels];
    modelCount = modelCount + 1;
  }
  struct TriSequences {
    TriSequence Sequence[*];
  };
  for (var i = 0; i < Header.numbodyparts; i = i + 1) {

    for (var j = 0; j < bodyparts[i].nummodels; j = j + 1) {
      struct ModelData {
        $shift_by(bodyparts[i].Models[j].vertinfoindex - current_offset);
        unsigned char VertexBones[bodyparts[i].Models[j].numverts];
        $shift_by(bodyparts[i].Models[j].norminfoindex - current_offset);
        unsigned char Normalbones[bodyparts[i].Models[j].numnorms];
        $shift_by(bodyparts[i].Models[j].vertindex - current_offset);
        Vector3 Vertices[bodyparts[i].Models[j].numverts];
        $shift_by(bodyparts[i].Models[j].normindex - current_offset);
        Vector3 Normals[bodyparts[i].Models[j].numnorms];
        $shift_by(bodyparts[i].Models[j].meshindex - current_offset);
        Mesh Meshs[bodyparts[i].Models[j].nummesh];
        for (var l = 0; l < bodyparts[i].Models[j].nummesh; l = l + 1) {
          $shift_by(Meshs[l].triindex - current_offset);

          TriSequences SequencesTri;
        }
      };
      ModelData modelData;
    }
  }

  // Mesh Meshs[Models[0].nummesh];

  // unsigned char TriSeq[Header.textureindex - Meshs[0].triindex];
        $shift_by(Header.textureindex - current_offset);
  TextureHeader TextureHeaders[Header.numtextures];

  unsigned short Skins[Header.numskinref * Header.numskinfamilies];

  for (var i = 0; i < Header.numtextures; i = i + 1) {
    struct TextureDataStruct {
      unsigned char Data[TextureHeaders[i].width * TextureHeaders[i].height];
      unsigned char Palette[256 * 3];
    };
    TextureDataStruct textureData;
  }
};