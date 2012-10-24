#ifndef PLATFORMFUNCTIONS_H
#define PLATFORMFUNCTIONS_H

#ifdef Q_WS_WIN
#include <qt_windows.h>
#endif

namespace PlatformFunctions
{
#ifdef Q_WS_WIN
    /*======================================================================
    Routine Description: This routine returns TRUE if the caller's
    process is a member of the Administrators local group. Caller is NOT
    expected to be impersonating anyone and is expected to be able to
    open its own process and process token.
    Arguments: None.
    Return Value:
    TRUE - Caller has Administrators local group.
    FALSE - Caller does not have Administrators local group.
    ======================================================================*/
    BOOL IsUserAdmin()
    {
        BOOL xBoolResult;
        SID_IDENTIFIER_AUTHORITY xNtAuthority = {SECURITY_NT_AUTHORITY};
        PSID xAdministratorsGroup = NULL;
        xBoolResult = AllocateAndInitializeSid(
                &xNtAuthority,
                2,
                SECURITY_BUILTIN_DOMAIN_RID,
                DOMAIN_ALIAS_RID_ADMINS,
                0, 0, 0, 0, 0, 0,
                &xAdministratorsGroup);

        if(xBoolResult == true)
        {
            BOOL xFunctionResult;
            xFunctionResult = CheckTokenMembership (NULL, xAdministratorsGroup, &xBoolResult);
            if (xFunctionResult == false)
            {
                xBoolResult = FALSE;
            }
            FreeSid(xAdministratorsGroup);
        }

        return(TRUE);
        //return(xBoolResult);
    }
    //====================================================================

    //Поднять права до админских
    bool logonAsAdmin()
    {
        LPTSTR lpszUsername = L"Admin"; //логин админа
        LPTSTR lpszDomain = NULL; //домен
        LPTSTR lpszPassword = L"passw"; //пароль админа
        HANDLE hToken; //маркер доступа(токен)

        //Получаем токен админа
        if(!LogonUser(lpszUsername, lpszDomain, lpszPassword, LOGON32_LOGON_INTERACTIVE,
                      LOGON32_PROVIDER_DEFAULT, &hToken))
            return false;

        //Прикидываемся админом
        if(!ImpersonateLoggedOnUser(hToken)) return false;

        return true;
    }
#else
    bool IsUserAdmin()
    {
        return true;
    }
#endif
}

#endif // PLATFORMFUNCTIONS_H
