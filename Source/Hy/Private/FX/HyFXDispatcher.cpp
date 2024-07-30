// Fill out your copyright notice in the Description page of Project Settings.


#include "FX/HyFXDispatcher.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Math/TransformNonVectorized.h"
#include "NiagaraSystem.h"

#include "GameFramework/Character.h"

#include "HyLogging.h"



void UHyFXDispatcher::PlayActionFX(const FHyActionEffect& effect, ACharacter* instigator)
{
    Internal_PlayEffect(instigator, effect);
}

void UHyFXDispatcher::Internal_PlayEffect(ACharacter* instigator, const FHyActionEffect& effect)
{
    if (instigator) 
    {
        effect.GetGuid().NewGuid();

        switch (effect.SpawnLocation) 
        {
        case ESpawnFXLocation::ESpawnOnActorLocation:
        case ESpawnFXLocation::ESpawnAttachedToSocketOrBone:
            SpawnFXAttached(effect, instigator); // 여기서는 AttachCom 정보를 FXMap에 저장 안함. 알아서 중단되도록..
            break;
        case ESpawnFXLocation::ESpawnAtLocation:
            SpawnFXAtLocation(FDispatchFX(effect, effect.RelativeOffset));
            break;
        default:
            //SpawnSoundAndParticleAttached(effect, instigator);
            break;
        }
    }
    else
    {
        ERR_V("instigator is null");
    }
}

FAttachedComponents UHyFXDispatcher::SpawnFXAttached(const FHyActionEffect& effect, ACharacter* instigator)
{
    FAttachedComponents comps;
    if (instigator)
    {
        effect.GetGuid().NewGuid();

        if (instigator->GetMesh()->DoesSocketExist(effect.SocketOrBoneName))
        {
            if (effect.ActionSound)
            {
                comps.AudioComp = UGameplayStatics::SpawnSoundAttached(effect.ActionSound, instigator->GetMesh(), effect.SocketOrBoneName);
            }

            if (effect.NiagaraParticle)
            {
                comps.NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(effect.NiagaraParticle, instigator->GetMesh(), effect.SocketOrBoneName,
                    effect.RelativeOffset.GetLocation(), effect.RelativeOffset.GetRotation().Rotator(), effect.RelativeOffset.GetScale3D(),
                    EAttachLocation::SnapToTarget, true, ENCPoolMethod::AutoRelease);
            }

            if (effect.PSParticle)
            {
                comps.CascadeComp = UGameplayStatics::SpawnEmitterAttached(effect.PSParticle, instigator->GetMesh(), effect.SocketOrBoneName,
                    effect.RelativeOffset.GetLocation(), effect.RelativeOffset.GetRotation().Rotator(), effect.RelativeOffset.GetScale3D());
            }
        
        }
        else
        {
            ERR_V("invalid socket name %s ", *effect.SocketOrBoneName.ToString());
        }
    }
    else
    {
        ERR_V("instigator is null");
    }
    

    return comps;

}

void UHyFXDispatcher::SpawnFXAtLocation(const FDispatchFX& effect)
{
    if (effect.ActionSound) 
    {
        UGameplayStatics::SpawnSoundAtLocation(this, effect.ActionSound, effect.SpawnLocation.GetLocation());
    }

    if (effect.NiagaraParticle) 
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, effect.NiagaraParticle, effect.SpawnLocation.GetLocation(),
            effect.SpawnLocation.GetRotation().Rotator(), effect.SpawnLocation.GetScale3D());
    }

    if (effect.PSParticle) 
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, effect.PSParticle, effect.SpawnLocation.GetLocation(),
            effect.SpawnLocation.GetRotation().Rotator(), effect.SpawnLocation.GetScale3D());
    }
}
