#ifndef _LOFTILI_H
#define _LOFTILI_H

#if defined(__APPLE__)
#define APPLE 1
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#define APPLE 0
#endif

#define WARN(X) spdlog::get(LOFTILI_SPDLOG_ID)->warn(X);
#define WARN_2(X, Y) spdlog::get(LOFTILI_SPDLOG_ID)->warn(X,Y);

#define INFO(X) spdlog::get(LOFTILI_SPDLOG_ID)->info(X);
#define INFO_2(X, Y) spdlog::get(LOFTILI_SPDLOG_ID)->info(X, Y);

#define CRITICAL(X) spdlog::get(LOFTILI_SPDLOG_ID)->critical(X);
#define CRITICAL_2(X, Y) spdlog::get(LOFTILI_SPDLOG_ID)->critical(X, Y);

#include "config.h"
#include "lib/typelist.h"
#include "api/registration.h"
#include "spdlog/spdlog.h"

#ifdef HAVE_AUDIO
#include "audio/playback.h"
#endif

namespace loftili {

typedef loftili::lib::generic::T_Seq<
  loftili::api::Registration,
#ifdef HAVE_AUDIO
  loftili::audio::Playback
#endif
>::T_Result ComponentList;

typedef loftili::lib::generic::T_ScatterHierarchy<ComponentList> T_ComponentHierarchy;

class ComponentHierarchy : public T_ComponentHierarchy {
  public:
    template <class T>
    T* Field() {
      typename T_ComponentHierarchy::template T_Rebind<T>::T_Result& r = *this;
      return &r.m_item;
    };
};

}

#endif
