//----------------------------------------------------
// File : XLoader.cpp
//
// DirectX X File Loader Library
//
// Date : May. 10, 2008
// Version : 1.0
// Author : Pocol
//----------------------------------------------------

//
// include
//
#include "XLoader.h"

//
// global Variables
//
static char* Pointer;
static char Token[1024];


//-------------------------------------------------------------------------------------------------
// Name : CheckToken()
// Desc : �w�肳�ꂽ������ƃg�[�N�����`�F�b�N����
//-------------------------------------------------------------------------------------------------
static bool CheckToken(const char* str)
{
	if ( strcmp(Token, str) == 0 )
		return true;
	else
		return false;
}

//-------------------------------------------------------------------------------------------------
// Name : GetToken()
// Desc : �g�[�N�����擾����
//-------------------------------------------------------------------------------------------------
static void GetToken()
{
	char *p = Pointer;
	char *q = Token;

	while ( *p != '\0' && strchr(" \t\r\n,;\"", *p) ) 
		p++;

	if ( *p == '{' || *p == '}' )
		(*q++) = (*p++);
	else
		while ( *p != '\0' && !strchr(" \t\r\n,;\"{}", *p ) )
			(*q++) = (*p++);

	Pointer = p;
	*q = '\0';
}

//--------------------------------------------------------------------------------------------------
// Name : GetToken()
// Desc : �g�[�N�����擾���w�肳�ꂽ��������r���s��
//--------------------------------------------------------------------------------------------------
static bool GetToken(const char* token)
{
	GetToken();
	if ( strcmp(Token, token) != 0 )
	{
		cout << "Error : �z��g�[�N���ƓǍ��g�[�N������v���܂���\n";
		cout << "�z��g�[�N���F" << token << endl;
		cout << "�Ǎ��g�[�N���F" << Token << endl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------
// Name : GetFloatToken()
// Desc : �g�[�N����float�^�ɕϊ����擾����
//--------------------------------------------------------------------------------------------------
static float GetFloatToken()
{
	GetToken();
	return (float)atof(Token);
}

//--------------------------------------------------------------------------------------------------
// Name : GetIntToken()
// Desc : �g�[�N����int�^�ɕϊ����擾����
//--------------------------------------------------------------------------------------------------
static int GetIntToken()
{
	GetToken();
	return (int)atoi(Token);
}

//-------------------------------------------------------------------------------------------------
// Name : SkipNode()
// Desc : �m�[�h���΂�
//-------------------------------------------------------------------------------------------------
static void SkipNode()
{
	while ( *Pointer != '\0' )
	{
		GetToken();
		if ( strchr(Token, '{' ) ) break;
	}
	int count = 1;
	while ( *Pointer != '\0' && count > 0 )
	{
		GetToken();
		if ( strchr(Token, '{' ) ) count++;
		else if ( strchr(Token, '}') ) count--;
	}
	if ( count > 0 )
	{
		cout << "Error : �J�b�R����v���Ă��܂���\n";
		return;
	}
}

////////////////////////////////////////////////////////////////////////
// XFace class
////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Name : XFace()
// Desc : �R���X�g���N�^
//-------------------------------------------------------------------------------------------------
XFace::XFace()
{
	element = 0;
	indexMaterial = -1;
	for(int i=0; i<4; i++ )
	{
		indexVertices[i] = -1;
		indexNormals[i] = -1;
		indexTexCoords[i] = -1;
	}
}

//--------------------------------------------------------------------------------------------------
// operator =
//--------------------------------------------------------------------------------------------------
XFace& XFace::operator =(XFace &ob)
{
	element = ob.element;
	indexMaterial = ob.indexMaterial;
	for(int i=0; i<4; i++ )
	{
		indexVertices[i] = ob.indexVertices[i];
		indexNormals[i] = ob.indexNormals[i];
		indexTexCoords[i] = ob.indexTexCoords[i];
	}
	return (*this);
}

//--------------------------------------------------------------------------------------------------
// Name : SetVertexIndex()
// Desc : ���_�C���f�b�N�X���Z�b�g����
//--------------------------------------------------------------------------------------------------
void XFace::SetVertexIndex(int index[])
{
	for ( int i=0; i<4; i++ ) indexVertices[i] = index[i];
}

//--------------------------------------------------------------------------------------------------
// Name : SetNormalIndex()
// Desc : �@���C���f�b�N�X���Z�b�g����
//--------------------------------------------------------------------------------------------------
void XFace::SetNormalIndex(int index[])
{
	for ( int i=0; i<4; i++ ) indexNormals[i] = index[i];
}

//--------------------------------------------------------------------------------------------------
// Name : SetTexCoordIndex()
// Desc : �e�N�X�`�����W�C���f�b�N�X���Z�b�g����
//--------------------------------------------------------------------------------------------------
void XFace::SetTexCoordIndex(int index[])
{
	for ( int i=0; i<4; i++ ) indexTexCoords[i] = index[i];
}

////////////////////////////////////////////////////////////////////////
// XMaterial class
////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------
// Name : XMaterial()
// Desc : �R���X�g���N�^
//--------------------------------------------------------------------------------------------------
XMaterial::XMaterial()
{
	strcpy(name, "null");
	ambient.r = 0.0f;	ambient.g = 0.0f;	ambient.b = 0.0f;	ambient.a = 0.0f;
	diffuse.r = 0.0f;	diffuse.g = 0.0f;	diffuse.b = 0.0f;	diffuse.a = 0.0f;
	specular.r = 0.0f;	specular.g = 0.0f;	specular.b = 0.0f;	specular.a = 0.0f;
	emissive.r = 0.0f;	emissive.g = 0.0f;	emissive.g = 0.0f;	emissive.a = 0.0f;
	power = 0.0f;
	strcpy(textureFileName, "null");
}

//--------------------------------------------------------------------------------------------------
// operator =
//--------------------------------------------------------------------------------------------------
XMaterial& XMaterial::operator =(XMaterial &ob)
{
	strcpy(name, ob.name);
	ambient = ob.ambient;
	diffuse = ob.diffuse;
	specular = ob.specular;
	emissive = ob.emissive;
	power = ob.power;
	strcpy(textureFileName, ob.textureFileName);
	return (*this);
}

//--------------------------------------------------------------------------------------------------
// Name : SetName()
// Desc : ���O���Z�b�g����
//--------------------------------------------------------------------------------------------------
void XMaterial::SetName(char *str)
{
	strcpy(name, str);
}

//--------------------------------------------------------------------------------------------------
// Name : SetTextureFileName()
// Desc : �e�N�X�`���t�@�C�������Z�b�g����
//--------------------------------------------------------------------------------------------------
void XMaterial::SetTextureFileName(char *str)
{
	strcpy(textureFileName, str);
}

////////////////////////////////////////////////////////////////////////
// XMesh class
////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------
// Name : XMesh()
// Desc : �R���X�g���N�^
//---------------------------------------------------------------------------------------------------
XMesh::XMesh()
{
	strcpy(name, "null");
	numVertices = 0;
	numNormals = 0;
	numTexCoords = 0;
	numFaces = 0;
	vertex = (XVector3*)malloc(1*sizeof(XVector3));
	normal = (XVector3*)malloc(1*sizeof(XVector3));
	texcoord = (XVector2*)malloc(1*sizeof(XVector2));
	face = (XFace*)malloc(1*sizeof(XFace));
}

//--------------------------------------------------------------------------------------------------
// operator =
//--------------------------------------------------------------------------------------------------
XMesh& XMesh::operator= (XMesh &ob)
{
	strcpy(name, ob.name);
	numVertices = ob.numVertices;
	numNormals = ob.numNormals;
	numTexCoords = ob.numTexCoords;
	numFaces = ob.numFaces;

	vertex = (XVector3*)malloc(numVertices*sizeof(XVector3));
	normal = (XVector3*)malloc(numNormals*sizeof(XVector3));
	texcoord = (XVector2*)malloc(numTexCoords*sizeof(XVector2));
	face = (XFace*)malloc(numFaces*sizeof(XFace));

	for(int i=0; i<numVertices; i++ )		vertex[i] = ob.vertex[i];
	for(int i=0; i<numNormals; i++ )		normal[i] = ob.normal[i];
	for(int i=0; i<numTexCoords; i++)		texcoord[i] = ob.texcoord[i];
	for(int i=0; i<numFaces; i++ )		face[i] = ob.face[i];
	
	return (*this);
}

//--------------------------------------------------------------------------------------------------
// Name : AddVertex()
// Desc : ���_��ǉ�����
//--------------------------------------------------------------------------------------------------
int XMesh::AddVertex(XVector3 &ob)
{
	numVertices++;
	vertex = (XVector3*)realloc(vertex, numVertices*sizeof(XVector3));
	vertex[numVertices-1] = ob;
	return numVertices;
}

//--------------------------------------------------------------------------------------------------
// Name : AddNormal()
// Desc : �@����ǉ�����
//--------------------------------------------------------------------------------------------------
int XMesh::AddNormal(XVector3 &ob)
{
	numNormals++;
	normal = (XVector3*)realloc(normal, numNormals*sizeof(XVector3));
	normal[numNormals-1] = ob;
	return numNormals;
}

//--------------------------------------------------------------------------------------------------
// Name : AddTexCoord()
// Desc : �e�N�X�`�����W��ǉ�����
//--------------------------------------------------------------------------------------------------
int XMesh::AddTexCoord(XVector2 &ob)
{
	numTexCoords++;
	texcoord = (XVector2*)realloc(texcoord, numTexCoords*sizeof(XVector2));
	texcoord[numTexCoords-1] = ob;
	return numTexCoords;
}

//--------------------------------------------------------------------------------------------------
// Name : AddFace()
// Desc : �ʂ�ǉ�����
//--------------------------------------------------------------------------------------------------
int XMesh::AddFace(XFace &ob)
{
	numFaces++;
	face = (XFace*)realloc(face, numFaces*sizeof(XFace));
	face[numFaces-1] = ob;
	return numFaces;
}

//--------------------------------------------------------------------------------------------------
// Name : Release()
// Desc : �m�ۂ������������������
//--------------------------------------------------------------------------------------------------
void XMesh::Release()
{
	if ( vertex )
	{
		free((XVector3*)vertex);
		vertex = NULL;
	}

	if ( normal )
	{
		free((XVector3*)normal);
		normal = NULL;
	}

	if ( texcoord )
	{
		free((XVector2*)texcoord);
		texcoord = NULL;
	}

	if ( face )
	{
		free((XFace*)face);
		face = NULL;
	}

	numVertices = 0;
	numNormals = 0;
	numTexCoords = 0;
	numFaces = 0;
}

//---------------------------------------------------------------------------------------------------
// Name : SetName()
// Desc : ���O���Z�b�g����
//---------------------------------------------------------------------------------------------------
void XMesh::SetName(char *str)
{
	strcpy(name, str);
}

////////////////////////////////////////////////////////////////////////
// XModel class
////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------
// Name : XModel()
// Desc : �R���X�g���N�^
//---------------------------------------------------------------------------------------------------
XModel::XModel()
{
	numMeshes = 0;
	numMaterials = 0;
	mesh = (XMesh*)malloc(1*sizeof(XMesh));
	material = (XMaterial*)malloc(1*sizeof(XMaterial));
}

//--------------------------------------------------------------------------------------------------
// Name : AddMesh()
// Desc : ���b�V����ǉ�����
//--------------------------------------------------------------------------------------------------
int XModel::AddMesh(XMesh ob)
{
	numMeshes++;
	mesh = (XMesh*)realloc(mesh, numMeshes*sizeof(XMesh));
	mesh[numMeshes-1] = ob;
	return numMeshes;
}

//--------------------------------------------------------------------------------------------------
// Name : AddMaterial()
// Desc : �}�e���A����ǉ�����
//--------------------------------------------------------------------------------------------------
int XModel::AddMaterial(XMaterial ob)
{
	numMaterials++;
	material = (XMaterial*)realloc(material, numMaterials*sizeof(XMaterial));
	material[numMaterials-1] = ob;
	return numMaterials;
}

//--------------------------------------------------------------------------------------------------
// Name : Release()
// Desc : �m�ۂ������������������
//--------------------------------------------------------------------------------------------------
void XModel::Release()
{
	if ( material )
	{
		free((XMaterial*)material);
		material = NULL;
	}
	if ( mesh )
	{
		free((XMesh*)mesh);
		mesh = NULL;
	}
	numMaterials = 0;
	numMeshes = 0;
}

//--------------------------------------------------------------------------------------------------
// Name : ComputeBoundingSphere()
// Desc : �o�E���f�B���O�X�t�B�A���v�Z����
//--------------------------------------------------------------------------------------------------
void XModel::ComputeBoundingSphere()
{
	int count = 0;
	float tempRadius = 0.0f;
	XVector3 tempCenter;
	tempCenter.x = 0.0f;
	tempCenter.y = 0.0f;
	tempCenter.z = 0.0f;

	//�@���S���W�̎Z�o
	for ( int i=0; i<numMeshes; i++ )
	{
		for ( int j=0; j<mesh[i].numVertices; j++ )
		{
			tempCenter.x += mesh[i].vertex[j].x;
			tempCenter.y += mesh[i].vertex[j].y;
			tempCenter.z += mesh[i].vertex[j].z;
			count++;
		}
	}
	tempCenter.x /= (float)count;
	tempCenter.y /= (float)count;
	tempCenter.z /= (float)count;

	//�@���a�̎Z�o
	for (int i=0; i<numMeshes; i++ )
	{
		for ( int j=0; j<mesh[i].numVertices; j++ )
		{
			float d = 0.0f;
			XVector3 temp;
			temp.x = mesh[i].vertex[j].x - tempCenter.x;
			temp.y = mesh[i].vertex[j].y - tempCenter.y;
			temp.z = mesh[i].vertex[j].z - tempCenter.z;
			d = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
			tempRadius = (tempRadius < d ) ? d : tempRadius;
		}
	}

	//�@���ʂ��i�[
	sphere.center = tempCenter;
	sphere.radius = tempRadius;
}

//--------------------------------------------------------------------------------------------------
// Name : ComputeBoundingBox()
// Desc : �o�E���f�B���O�{�b�N�X���v�Z����
//--------------------------------------------------------------------------------------------------
void XModel::ComputeBoundingBox()
{
	XVector3 tempMin, tempMax;

	//�@�ŏ��̒��_�ŏ�����
	tempMin = tempMax = mesh[0].vertex[0];

	for ( int i=0; i<numMeshes; i++ )
	{
		for ( int j=0; j<mesh[i].numVertices; j++ )
		{
			//�@x����
			if ( tempMin.x > mesh[i].vertex[j].x ) tempMin.x = mesh[i].vertex[j].x;
			if ( tempMax.x < mesh[i].vertex[j].x ) tempMax.x = mesh[i].vertex[j].x;

			//�@y����
			if ( tempMin.y > mesh[i].vertex[j].y ) tempMin.y = mesh[i].vertex[j].y;
			if ( tempMax.y < mesh[i].vertex[j].y ) tempMax.y = mesh[i].vertex[j].y;

			//�@z����
			if ( tempMin.z > mesh[i].vertex[j].z ) tempMin.z = mesh[i].vertex[j].z;
			if ( tempMax.z < mesh[i].vertex[j].z ) tempMax.z = mesh[i].vertex[j].z;
		}
	}

	//�@���ʂ��i�[
	box.min = tempMin;
	box.max = tempMax;
}

//--------------------------------------------------------------------------------------------------
// Name : Load()
// Desc : �e�L�X�g�t�H�[�}�b�g��X�t�@�C�������[�h����
//--------------------------------------------------------------------------------------------------
bool XModel::Load(char *filename)
{
	//�@�J�E���g�p�ϐ��Ȃ�	
	bool b_Mesh = false;
	int matCount = 0;
	int vertCount = 0;
	int faceCount = 0;
	int normCount = 0;
	int uvCount = 0;
	int meshCount = 0;
	
	XFace* tempFace;
	XMesh tempMesh;

	//�@�t�@�C����ǂݍ���
	HANDLE file = CreateFileA(
		filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	//�@�`�F�b�N
	if ( file == INVALID_HANDLE_VALUE )
	{
		cout << "Error : �w�肳�ꂽ�t�@�C���̓ǂݍ��݂Ɏ��s���܂���\n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	//�@�t�@�C���T�C�Y���擾
	DWORD size = GetFileSize(file, NULL);
	char* buffer = new char[size+1];
	buffer[size] = '\0';

	//�@�o�b�t�@�Ɋi�[
	DWORD read_size;
	ReadFile(file, buffer, size, &read_size, NULL);

	//�@�t�@�C�������
	CloseHandle(file);

	//�@�T�C�Y�`�F�b�N
	if ( read_size != size )
	{
		cout << "Error : �ǂݍ��݃T�C�Y�ƃT�C�Y����v���Ă��܂���\n";
		return false;
	}

	//�@Pointer�ɓǂݍ��񂾃o�b�t�@���Z�b�g
	Pointer = buffer;

	//�@���[�v
	while ( *Pointer != '\0' )
	{
		//�@�g�[�N�����擾
		GetToken();

		//�@template�̏ꍇ
		if ( CheckToken("template") )
		{
			//�@�X�L�b�v����
			SkipNode();
		}

		//�@Mesh�̏ꍇ
		else if ( CheckToken("Mesh") )
		{
			//�@�g�[�N�����擾
			GetToken();

			//�@�g�[�N����" { " �łȂ��ꍇ
			if ( !CheckToken("{") )
			{
				//�@���O���Z�b�g
				tempMesh.SetName(Token);

				//�@�g�[�N�����擾
				GetToken("{");
			}

			//�@�g�[�N����" { "�̏ꍇ
			else
			{
				//�@���O�����߂�
				char tempName[MAX_PATH] = "obj";
				sprintf(tempName, "%s%d", tempName, meshCount+1);

				//�@���O���Z�b�g
				tempMesh.SetName(tempName);
			}

			//�@���b�V�������J�E���g����
			meshCount++;

			//�@�J�E���g����1���傫���ꍇ
			if ( meshCount > 1 )
			{
				//�@�ʃf�[�^��ǉ�
				for(int i=0; i<faceCount; i++ )
					tempMesh.AddFace(tempFace[i]);
				
				//�@���b�V����ǉ�
				AddMesh(tempMesh);

				//�@�m�ۂ��������������
				SafeDeleteArray(tempFace);

				//�@�[���ɖ߂�
				ZeroMemory(&tempMesh, sizeof(tempMesh));
			}

			//�@���_���̃J�E���^�[��0�ɖ߂�
			vertCount = 0;

			//�@�g�[�N�����璸�_�����擾
			vertCount = GetIntToken();

			for( int i=0; i<vertCount; i++ )
			{
				//�@�g�[�N�����璸�_�f�[�^���擾
				XVector3 tempVertex;
				tempVertex.x = GetFloatToken();
				tempVertex.y = GetFloatToken();
				tempVertex.z = GetFloatToken();

				//�@���_�f�[�^��ǉ�
				tempMesh.AddVertex(tempVertex);
			}

			//�@���_�����`�F�b�N
			if ( tempMesh.numVertices != vertCount )
			{
				cout << "Error : ���_������v���Ă��܂���\n";
				return false;
			}

			//�@�ʐ��̃J�E���^�[��0�ɖ߂�
			faceCount = 0;

			//�@�g�[�N������ʐ����擾
			faceCount = GetIntToken();

			//�@���������m��
			tempFace = new XFace[faceCount];

			//�@�g�[�N������ʃf�[�^���擾
			for( int i=0; i<faceCount; i++ )
			{
				int tempIndex[4] = { -1, -1, -1, -1 };
				tempFace[i].element = 0;
				tempFace[i].indexMaterial = -1;

				//�@�g�[�N�����擾
				GetToken();
			
				//�@�O�p�`�̏ꍇ
				if ( CheckToken("3") )
				{
					//�@�v�f����3�ɂ���
					tempFace[i].element = 3;

					//�@�g�[�N�����璸�_�C���f�b�N�X���擾
					for( int j=0; j<3; j++ )
					{
						tempIndex[j] = GetIntToken();
					}

					//�@4�Ԗڂ̃C���f�b�N�X�ɂ�-1���i�[
					tempIndex[3] = -1;

					//�@���_�C���f�b�N�X���Z�b�g
					tempFace[i].SetVertexIndex(tempIndex);

					//�@�e�N�X�`�����W�C���f�b�N�X���Z�b�g
					tempFace[i].SetTexCoordIndex(tempIndex);
				}

				//�@�l�p�`�̏ꍇ
				else if ( CheckToken("4") )
				{
					//�@�v�f����4�ɂ���
					tempFace[i].element = 4;

					//�@�g�[�N�����璸�_�C���f�b�N�X���擾
					for ( int j=0; j<4; j++ )
					{
						tempIndex[j] = GetIntToken();
					}

					//�@���_�C���f�b�N�X���Z�b�g
					tempFace[i].SetVertexIndex(tempIndex);

					//�@�e�N�X�`�����W�C���f�b�N�X���Z�b�g
					tempFace[i].SetTexCoordIndex(tempIndex);
				}
			}
		}

		//�@MeshNormals�̏ꍇ
		else if ( CheckToken("MeshNormals") )
		{
			//�@�g�[�N�����擾
			GetToken("{");

			//�@�@�����̃J�E���^�[��0�ɖ߂�
			normCount = 0;

			//�@�g�[�N������@�������擾
			normCount = GetIntToken();

			//�@�g�[�N������@���f�[�^���擾
			for ( int i=0; i<normCount; i++ )
			{
				XVector3 tempNormal;
				tempNormal.x = GetFloatToken();
				tempNormal.y = GetFloatToken();
				tempNormal.z = GetFloatToken();

				//�@�@���f�[�^��ǉ�
				tempMesh.AddNormal(tempNormal);
			}

			//�@�@�������`�F�b�N
			if ( tempMesh.numNormals != normCount )
			{
				cout << "Error : �@��������v���Ă��܂���\n";
				return false;
			}

			//�@�@���C���f�b�N�X�����`�F�b�N
			if ( GetIntToken() != faceCount )
			{
				cout << "Error : �ʐ��Ɩ@���C���f�b�N�X������v���Ă��܂���\n";
				return false;
			}

			for ( int i=0; i<normCount; i++ )
			{
				int tempIndex[4] = { -1, -1, -1, -1 };

				//�@�g�[�N�����擾
				GetToken();

				//�@�O�p�`�̏ꍇ
				if ( CheckToken("3") )
				{
					//�@�g�[�N������@���C���f�b�N�X���擾
					for ( int j=0; j<3; j++ )
					{
						tempIndex[j] = GetIntToken();
					}

					//�@4�Ԗڂ̃C���f�b�N�X�ɂ�-1���Z�b�g
					tempIndex[3] = -1;

					//�@�@���C���f�b�N�X���Z�b�g
					tempFace[i].SetNormalIndex(tempIndex);
				}

				//�@�l�p�`�̏ꍇ
				else if( CheckToken("4") )
				{
					//�@�@���C���f�b�N�X���擾
					for ( int j=0; j<4; j++ )
					{
						tempIndex[j] = GetIntToken();
					}
					
					//�@�@���C���f�b�N�X���Z�b�g
					tempFace[i].SetNormalIndex(tempIndex);
				}
			}
		}

		//�@MeshTextureCoords�̏ꍇ
		else if ( CheckToken("MeshTextureCoords") )
		{
			//�@�g�[�N�����擾
			GetToken("{");

			//�@�e�N�X�`�����W���̃J�E���^�[��0�ɖ߂�
			uvCount = 0;

			//�@�g�[�N������e�N�X�`�����W�����擾
			uvCount = GetIntToken();

			for ( int i=0; i<uvCount; i++ )
			{
				//�@�g�[�N������e�N�X�`�����W�f�[�^���擾
				XVector2 tempUV;
				tempUV.x = GetFloatToken();
				tempUV.y = GetFloatToken();

				//�@�e�N�X�`�����W�f�[�^��ǉ�
				tempMesh.AddTexCoord(tempUV);
			}
		}

		//�@MeshMaterialList�̏ꍇ
		else if ( CheckToken("MeshMaterialList") )
		{
			//�@�g�[�N�����擾
			GetToken("{");

			//�@�}�e���A�����̃J�E���^�[��0�ɖ߂�
			matCount = 0;

			//�@�g�[�N������}�e���A�������擾
			matCount = GetIntToken();

			//�@�}�e���A�������`�F�b�N
			if ( GetIntToken() != faceCount )
			{
				cout << "Error : �ʐ��ƃ}�e���A�����X�g������v���܂���\n";
				return false;
			}

			//�@�g�[�N������}�e���A���C���f�b�N�X���擾
			for ( int i=0; i<faceCount; i++ )
			{
				tempFace[i].indexMaterial = GetIntToken();
			}

			for ( int i=0; i<matCount; i++ )
			{
				XMaterial tempMaterial;
			
				//�@�g�[�N�����擾
				GetToken("Material");
				GetToken();

				//�@�g�[�N����" { "�łȂ��ꍇ
				if ( !CheckToken("{") )
				{
					//�@���O���Z�b�g
					tempMaterial.SetName(Token);
				
					//�@�g�[�N�����擾
					GetToken("{");
				}

				//�@�g�[�N����" { "�̏ꍇ
				else
				{
					//�@���O�����߂�
					char tempName[MAX_PATH] = "mat";
					sprintf(tempName, "%s%d", tempName, i+1);
		
					//�@���O���Z�b�g
					tempMaterial.SetName(tempName);
				}

				//�@Ambient Color
				tempMaterial.ambient.r = 0.15f;
				tempMaterial.ambient.g = 0.15f;
				tempMaterial.ambient.g = 0.15f;
				tempMaterial.ambient.a = 1.0f;

				//�@Diffuse Color
				tempMaterial.diffuse.r = GetFloatToken();
				tempMaterial.diffuse.g = GetFloatToken();
				tempMaterial.diffuse.b = GetFloatToken();
				tempMaterial.diffuse.a = GetFloatToken();

				//�@Shiness
				tempMaterial.power = GetFloatToken();

				//�@Specular Color
				tempMaterial.specular.r = GetFloatToken();
				tempMaterial.specular.g = GetFloatToken();
				tempMaterial.specular.b = GetFloatToken();
				tempMaterial.specular.a = 1.0f;

				//�@Emissive Color
				tempMaterial.emissive.r = GetFloatToken();
				tempMaterial.emissive.g = GetFloatToken();
				tempMaterial.emissive.b = GetFloatToken();
				tempMaterial.emissive.a = 1.0f;

				//�@�g�[�N�����擾
				GetToken();

				//�@TextureFileName�̏ꍇ
				if ( CheckToken("TextureFileName") )
				{
					//�@�g�[�N�����擾
					GetToken("{");

					//�@�g�[�N�����擾
					GetToken();

					//�@�t�@�C�������Z�b�g
					tempMaterial.SetTextureFileName(Token);

					//�@�g�[�N�����擾
					GetToken("}");
				}

				//�@�g�[�N����" } "�̏ꍇ
				else if ( CheckToken("}") )
				{
					//�@�}�e���A���f�[�^��ǉ�
					AddMaterial(tempMaterial);
				}
			}
		}
	}

	//�@���b�V������1�ȏ�̏ꍇ
	if ( meshCount >= 1 )
	{
		//�@�ʃf�[�^��ǉ�
		for ( int i=0; i<faceCount; i++ )
			tempMesh.AddFace(tempFace[i]);
		
		//�@���b�V���f�[�^��ǉ�
		AddMesh(tempMesh);

		//�@�m�ۂ��������������
		SafeDeleteArray(tempFace);
	}

	//�@�o�E���f�B���O�X�t�B�A���v�Z
	ComputeBoundingSphere();

	//�@�o�E���f�B���O�{�b�N�X���v�Z
	ComputeBoundingBox();

	return true;
}

//---------------------------------------------------------------------------------------------------
// Name : Render()
// Desc : ���b�V���̃C���f�b�N�X���w�肵�ĕ`��
//---------------------------------------------------------------------------------------------------
void XModel::Render(int index, float scale)
{
	int pre_mat = -1;
	int cur_mat = 0;
	bool exist_material = false;
	bool exist_texcoord = false;
	bool exist_normal = false;

	if ( numMaterials > 0 ) exist_material = true;
	if ( mesh[index].numTexCoords > 0 ) exist_texcoord = true;
	if ( mesh[index].numNormals > 0 ) exist_normal = true;

	for ( int i=0; i<mesh[index].numFaces; i++ )
	{
		//�@�}�e���A�������݂���ꍇ
		if ( exist_material )
		{
			//�@�}�e���A���C���f�b�N�X���擾
			cur_mat = mesh[index].face[i].indexMaterial;

			//�@�}�e���A���C���f�b�N�X���قȂ�ꍇ
			if ( cur_mat != pre_mat )
			{
				//�@��{�F
				glColor4fv(material[cur_mat].diffuse);

				//�@Ambient Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material[cur_mat].ambient);

				//�@Diffuse Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material[cur_mat].diffuse);

				//�@Specular Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material[cur_mat].specular);

				//�@Emissive Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material[cur_mat].emissive);

				//�@Shininess
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material[cur_mat].power);

				//�@�}�e���A���C���f�b�N�X���X�V
				pre_mat = cur_mat;
			}
		}

		//�@�v�f����3�̏ꍇ
		if ( mesh[index].face[i].element == 3 ) 
			glBegin(GL_TRIANGLES);

		//�@�v�f����4�̏ꍇ
		else if ( mesh[index].face[i].element == 4 )
			glBegin(GL_QUADS);

		for ( int j=0; j<mesh[index].face[i].element; j++ )
		{
			//�@�e�N�X�`�����W�����݂���ꍇ
			if ( exist_texcoord )
				glTexCoord2fv(mesh[index].texcoord[mesh[index].face[i].indexTexCoords[j]]);

			//�@�@���x�N�g�������݂���ꍇ
			if ( exist_normal )
				glNormal3fv(mesh[index].normal[mesh[index].face[i].indexNormals[j]]);
			
			//�@���_���W
			glVertex3f(
				mesh[index].vertex[mesh[index].face[i].indexVertices[j]].x * scale,
				mesh[index].vertex[mesh[index].face[i].indexVertices[j]].y * scale,
				mesh[index].vertex[mesh[index].face[i].indexVertices[j]].z * scale );
		}

		//�@
		glEnd();
	}
}

//---------------------------------------------------------------------------------------------------
// Name : Render()
// Desc : �`�揈��
//---------------------------------------------------------------------------------------------------
void XModel::Render(float scale)
{
	for ( int i=0; i<numMeshes; i++ )
	{
		Render(i, scale);
	}
}