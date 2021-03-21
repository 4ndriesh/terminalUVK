#ifndef MANAGE_DEFINE_H
#define MANAGE_DEFINE_H

#define Q_PROPERTY_RWN(type,n) Q_PROPERTY(type n READ n WRITE set##n NOTIFY n##Changed ) \
    public: \
    type m_##n; \
    void set##n(const type &p){ \
    if(m_##n!=p){ \
    m_##n=p; \
    emit n##Changed();}} \
    const type &n()const  {return m_##n;}
#define Q_PROPERTY_RN(type,n) Q_PROPERTY(type n READ n NOTIFY n##Changed ) \
    public: \
    type m_##n; \
    const type &n()const  {return m_##n;}
#define Q_PROPERTY_RW(type,n) Q_PROPERTY(type n READ n WRITE set##n) \
    public: \
    type m_##n; \
    void set##n(const type &p){ \
    if(m_##n!=p){ \
    m_##n=p;}} \
    const type &n()const  {return m_##n;}
#endif // MANAGE_DEFINE_H
