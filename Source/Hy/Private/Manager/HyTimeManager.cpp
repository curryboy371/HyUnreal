// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HyTimeManager.h"

void UHyTimeManager::SetTimerFunc(float Delay, TFunction<void()> FunctionToCall)
{
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [FunctionToCall]()
        {
            // 타이머 콜백으로 받은 함수 포인터를 호출
            if (FunctionToCall)
            {
                FunctionToCall();
            }
        }, Delay, false);

}
