union  foo {int i; double d;};
enum Type {Int, Double};
struct bar {
    enum Type type;
    union foo u;
};
int main (void)
{
    struct bar x;
    x.u.d  = 12.34;
    x.type = Double;
}
