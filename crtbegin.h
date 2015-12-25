#ifndef CRTBEGIN_H
#define CRTBEGIN_H


extern void *__dso_handle;

struct DObjs
{
  void (*dtor_) (void *);
  void *arg_;
  void *dso_handle_;
};

void g_dtor();

#endif
