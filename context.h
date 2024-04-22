#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
public:
    Context();

    static int getContext();
    static void setContext(const int id_user);

private:
    static int current_user_id;
};

#endif // CONTEXT_H
