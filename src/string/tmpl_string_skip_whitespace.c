

extern void tmpl_String_Skip_Whitespace(const char ** const str_ptr);

void tmpl_String_Skip_Whitespace(const char ** const str_ptr)
{
    const char *str;

    if (!str_ptr)
        return;

    str = *str_ptr;

    if (!str)
        return;

    while (*str == ' ')
        ++str;
}
