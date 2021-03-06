/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2020-02-10 16:51:42
 * @LastEditTime: 2020-02-10 17:34:41
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */

#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "sem.h"


/* 信号量初始化（赋值）函数*/
int init_sem(int sem_id, int init_value)
{
    union semun sem_union;
    sem_union.val = init_value; /* init_value 为初始值 */

    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
        perror("Initialize semaphore");
        return -1;
    }

    return 0;
}

/* 从系统中删除信号量的函数 */
int del_sem(int sem_id)
{
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        perror("Delete semaphore");
        return -1;
    }
}

/* P 操作函数 */
int sem_p(int sem_id)
{
    struct sembuf sops;
    sops.sem_num = 0; /* 单个信号量的编号应该为 0 */
    sops.sem_op = -1; /* 表示 P 操作 */
    sops.sem_flg = SEM_UNDO; /* 系统自动释放将会在系统中残留的信号量*/

    if (semop(sem_id, &sops, 1) == -1)
    {
        perror("P operation");
        return -1;
    }
    return 0;
}

/* V 操作函数*/
int sem_v(int sem_id)
{
    struct sembuf sops;
    sops.sem_num = 0; /* 单个信号量的编号应该为 0 */
    sops.sem_op = 1; /* 表示 V 操作 */
    sops.sem_flg = SEM_UNDO; /* 系统自动释放将会在系统中残留的信号量*/

    if (semop(sem_id, &sops, 1) == -1)
    {
        perror("V operation");
        return -1;
    }
    return 0;
}
