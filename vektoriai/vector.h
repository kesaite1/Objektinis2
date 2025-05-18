
template <typename T>
class Vector {

    private:
    T* data;

    public:
    Vector();
    ~Vector();

    void push_back(const T& value);
    void pop_back(const T& value);
    void reallocate(size_t new_capacity);
    T& operator[](size_t index);
    T& at(size_t index);
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;


};