/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright (c) 2006-2015 The Open Group                                    */
/*                                                                           */
/* Permission is hereby granted, free of charge, to any person obtaining a   */
/* copy of this software (the "Software"), to deal in the Software without   */
/* restriction, including without limitation the rights to use, copy,        */
/* modify, merge, publish, distribute, sublicense, and/or sell copies of     */
/* the Software, and to permit persons to whom the Software is furnished     */
/* to do so, subject to the following conditions:                            */
/*                                                                           */
/* The above copyright notice and this permission notice shall be included   */
/* in all copies or substantial portions of the Software.                    */
/*                                                                           */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.    */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY      */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT */
/* OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR  */
/* THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                */
/*                                                                           */
/* ------------------------------------------------------------------------- */

/**
 * @file cmpipl.h
 * @brief This header verifies that a valid CMPI_PLATFORM_{xxx}
 * symbol has been defined; MIs do not need to include this header because it
 * is included by `cmpift.h`.
 *
 * This header file belongs to the Technical Standard: Systems Management:
 * Common Manageability Programming Interface (CMPI) Issue 2 Version 1.
 *
 * This header file is provided as a convenience only. In the case of any
 * discrepancy between the header file and the Technical Standard
 * (incorporating any subsequent Technical Corrigenda), the Technical Standard
 * shall be definitive.
 */

#ifndef _CMPIPL_H_
#define _CMPIPL_H_

// We need to define the defgroup here, even in the same Doxygen comment as
// the actual content, because this group does not define any C/C++ entity.
/**
 * @addtogroup symbols-user
 * @{
 * @defgroup sym-platform CMPI_PLATFORM_{xxx}
 * @{
 * @brief Compile platform for CMPI
 *
 * The symbols for the compile platform have names of the format:<br/>
 *
 * <div style="margin-left:20px">
 *   <b>CMPI_PLATFORM_{os}_{mach}_{comp}</b><br/>
 * </div>
 *
 * where <b>{os}</b> indicates the operating system,
 * <b>{mach}</b> indicates the machine architecture,
 * and <b>{comp}</b> indicates the C/C++ compiler.
 *
 * The valid symbols for the CMPI compile platform are:
 *
 *   * CMPI_PLATFORM_LINUX_GENERIC_GNU
 *   * CMPI_PLATFORM_HPUX_ACC
 *   * CMPI_PLATFORM_WIN32_IX86_MSVC
 *   * CMPI_PLATFORM_SOLARIS_SPARC_GNU
 *   * CMPI_PLATFORM_SOLARIS_SPARC_CC
 *   * CMPI_PLATFORM_AIX_RS_IBMCXX
 *   * CMPI_PLATFORM_ZOS_ZSERIES_IBM
 *   * CMPI_PLATFORM_TRU64_ALPHA_DECCXX
 *   * CMPI_PLATFORM_OS400_ISERIES_IBM
 *   * CMPI_PLATFORM_DARWIN_PPC_GNU
 *   * CMPI_PLATFORM_VMS_ALPHA_DECCXX
 *   * CMPI_PLATFORM_VMS_IA64_DECCXX
 *
 * There is no default compile platform; the user of the CMPI header files needs
 * to define exactly one of these symbols.
 *
 * The `cmpipl.h` header file verifies that exactly one of these symbols has
 * been defined.
 * @}
 * @}
 */

#if defined(CMPI_PLATFORM_LINUX_GENERIC_GNU) + \
    defined(CMPI_PLATFORM_HPUX_ACC) + \
    defined(CMPI_PLATFORM_WIN32_IX86_MSVC) + \
    defined(CMPI_PLATFORM_SOLARIS_SPARC_GNU) + \
    defined(CMPI_PLATFORM_SOLARIS_SPARC_CC) + \
    defined(CMPI_PLATFORM_AIX_RS_IBMCXX) + \
    defined(CMPI_PLATFORM_ZOS_ZSERIES_IBM) + \
    defined(CMPI_PLATFORM_TRU64_ALPHA_DECCXX) + \
    defined(CMPI_PLATFORM_OS400_ISERIES_IBM) + \
    defined(CMPI_PLATFORM_DARWIN_PPC_GNU) + \
    defined(CMPI_PLATFORM_VMS_ALPHA_DECCXX) + \
    defined(CMPI_PLATFORM_VMS_IA64_DECCXX) != 1
#  error "You have not defined a valid platform for CMPI. The choices are:"
#  error "  CMPI_PLATFORM_LINUX_GENERIC_GNU"
#  error "  CMPI_PLATFORM_HPUX_ACC"
#  error "  CMPI_PLATFORM_WIN32_IX86_MSVC"
#  error "  CMPI_PLATFORM_SOLARIS_SPARC_GNU"
#  error "  CMPI_PLATFORM_SOLARIS_SPARC_CC"
#  error "  CMPI_PLATFORM_AIX_RS_IBMCXX"
#  error "  CMPI_PLATFORM_ZOS_ZSERIES_IBM"
#  error "  CMPI_PLATFORM_TRU64_ALPHA_DECCXX"
#  error "  CMPI_PLATFORM_OS400_ISERIES_IBM"
#  error "  CMPI_PLATFORM_DARWIN_PPC_GNU"
#  error "  CMPI_PLATFORM_VMS_ALPHA_DECCXX"
#  error "  CMPI_PLATFORM_VMS_IA64_DECCXX"
#endif

#endif // _CMPIPL_H_
