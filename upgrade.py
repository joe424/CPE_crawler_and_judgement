#!/usr/bin/env python
# coding: utf-8

# In[1]:


import os
from shutil import copyfile


# In[2]:


compile_failed = os.system('g++ compare.cpp -o compare.exe')


# In[3]:


if not compile_failed:
    d_name = os.path.join(os.getcwd(), 'CPE')
    if os.path.exists(d_name):
        for f1 in os.listdir(d_name):
            for f2 in os.listdir(os.path.join(d_name, f1)):
                if os.path.isfile(os.path.join(d_name, f1, f2, 'compare.exe')):
                    os.remove(os.path.join(d_name, f1, f2, 'compare.exe'))
                copyfile(os.path.join(os.getcwd(), 'compare.exe'), os.path.join(d_name, f1, f2, 'compare.exe'))


    else:
        print("folder 'CPE' not exist!")
else:
    print("compile failed!")


# In[ ]:




