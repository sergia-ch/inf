size_t my_strlen(const char *s)
{
    int i = 0;
    while(*s++) i++;
    return(i);
}
