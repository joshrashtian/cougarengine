#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID = 0;
};

#endif