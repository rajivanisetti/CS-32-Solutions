void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (m->menuItems() == NULL || m->menuItems()->size() == 0)
    {
        return;
    }
    
    for (vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
    {
        if (path == "")
        {
            cout << (*it)->name() << endl;
            listAll(*it, (*it)->name());
        }
        else
        {
            cout << path + "/" + (*it)->name() << endl;
            listAll(*it,  path + "/" + (*it)->name());
        }
    }
}
