#ifndef PURECPP_H
#define PURECPP_H

#define UNUSED(x)                   (void)(x)
#define START_FUNC()                std::cout<<"--- Start "<<__PRETTY_FUNCTION__<<std::endl
#define SHOW_NAME_AND_RESULT(n)     std::cout<<#n" return "<< (n)<<std::endl

#endif // PURECPP_H
