#ifndef Object_hpp
#define Object_hpp

#include <GL/glew.h>
//図形データ
class Object
{
    //頂点配列オブジェクト名
    GLuint vao;
    //頂点バッファオブジェクト名
    GLuint vbo;
    //インデックスの頂点バッファオブジェクト
    GLuint ibo;
public:
    //頂点属性
    struct Vertex{
        //位置
        GLfloat position[3];
        //色
        GLfloat color[3];
    };
    //頂点配列オブジェクトの結合
    void bind() const {
        //描画する頂点配列オブジェクトを指定する
        glBindVertexArray(vao);
    }
    //コンストラクタ
    // size: 頂点の位置の次元
    // vertexcount: 頂点の数
    // vertex: 頂点属性を格納した配列
    // indexcount: 頂点のインデックスの要素数
    // index: 頂点のインデックスを格納した配列
    Object(GLint size, GLsizei vertexcount, const Vertex *vertex,
           GLsizei indexcount = 0, const GLuint *index = NULL)
    {
        // 頂点配列オブジェクト
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        // 頂点バッファオブジェクト
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
        vertexcount * sizeof (Vertex), vertex, GL_STATIC_DRAW);
        // 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
        //頂点座標をvertexArrayObjectの0番にバインド//変数はvertexShaderでvarying変数として宣言,番号はmain関数で指定済み
        //p175にmain関数ではなくshader側で番号を指定する方法が記載されている．
        glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, sizeof (Vertex), static_cast<Vertex *>(0)->position);
        glEnableVertexAttribArray(0);
        // 色座標をvertexArrayObjectの1番にバインド
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex *>(0)->color);
        glEnableVertexAttribArray(1);
        
        // インデックスの頂点バッファオブジェクト
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indexcount * sizeof (GLuint), index, GL_STATIC_DRAW);
    }
    // デストラクタ
    virtual ~Object()
    {
        // 頂点配列オブジェクトを削除する
        glDeleteVertexArrays(1, &vao);
        
        // 頂点バッファオブジェクトを削除する
        glDeleteBuffers(1, &vbo);
        
        // インデックスの頂点バッファオブジェクトを削除する
        glDeleteBuffers(1, &ibo);
    }
    
private:
    // コピーコンストラクタによるコピー禁止
    Object(const Object &o);
    // 代入によるコピー禁止
    Object &operator=(const Object &o);
};

#endif /* Object_hpp */
