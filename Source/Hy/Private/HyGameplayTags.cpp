// Fill out your copyright notice in the Description page of Project Settings.


#include "HyGameplayTags.h"
#include "HyLogging.h"


void FHyGameplayTags::InitializeTags()
{
    // TODO Container 비교가 유용한 경우도 있으나 ( A.B.C.D == {A.B.C.D, A.B.G.D, A.C.A}
    // 상위 태그까지의 비교 (Match)가 효율적인 경우도 있으니 ( A.B.C.D == A.B.C )
    // 둘을 잘 섞어서 사용해야함
    // 현재는 테스트 해보느라 컨테이너 태그를 주로 비교에 사용중이라 비효율적

    FHyGameplayTags& instance = FHyGameplayTags::Get();
    instance.TupleArray.Reset();

    /*
    
    Action.Stand

    // 쓰러져있는지
    Action.Down

    // Normal 상태인지
    Action.Stand.Normal

    // Attack 상태인지
    Action.Stand.Attack

    // Skill 상태인지
    // Action.Stand.Skill


    // Damaged 중인지
    // Action.Stand.Damaged
    // Action.Down.Damanged

    // Hit 상태
    // Hit
    // Knockback
    // Knockdown
    // stun

    */

    instance.AddContainerTag(FName("Action.Stand"), instance.StandTuple.Stand); // 서있는 상태인지
    instance.AddContainerTag(FName("Action.Down"), instance.StandTuple.Down);   // 다운된 상태인지

    instance.AddContainerTag(FName("Action.Stand.Normal"), instance.NormalTuple);   // 노말 상태인지
    instance.AddContainerTag(FName("Action.Stand.Skill"), instance.SkillTuple);     // 스킬 상태인지
    instance.AddContainerTag(FName("Action.Stand.Attack"), instance.AttackTuple);   // 공격 상태인지

    instance.AddContainerTag(FName("Damaged"), instance.DamagedParentTuple);        // 대미지 상태인지

    instance.AddContainerTag(FName("Damaged.Hit"), instance.DamagedTuple.Hit);      
    instance.AddContainerTag(FName("Damaged.Knockback"), instance.DamagedTuple.Knockback);
    instance.AddContainerTag(FName("Damaged.Knockdown"), instance.DamagedTuple.Knockdown);
    instance.AddContainerTag(FName("Damaged.Stun"), instance.DamagedTuple.Stun);

    instance.AddContainerTag(FName("Dead"), instance.DeadTuple);                    // 죽은 상태인지


    instance.AddActionTag(FName("Action.Stand.Normal.Spawn"), instance.ActionSpawn);
    instance.AddActionTag(FName("Action.Stand.Normal.Idle"), instance.ActionIdle);
    instance.AddActionTag(FName("Action.Stand.Normal.Walk"), instance.ActionWalk);
    instance.AddActionTag(FName("Action.Stand.Normal.Run"), instance.ActionRun);

    instance.AddActionTag(FName("Action.Stand.Attack.Dashing"), instance.ActionAttackDash);
    instance.AddActionTag(FName("Action.Stand.Attack.Attacking"), instance.ActionAttack);
    instance.AddActionTag(FName("Action.Stand.Attack.Skill1"), instance.ActionSkill);
    instance.AddActionTag(FName("Action.Stand.Skill.Dash"), instance.ActionDash);
    instance.AddActionTag(FName("Action.Stand.Skill.Evade"), instance.ActionEvade);
    instance.AddActionTag(FName("Action.Stand.Attack.Test"), instance.ActionTest);


    instance.AddActionTag(FName("Action.Stand.Damaged.Standing"), instance.ActionHitTransit.Stand);
    instance.AddActionTag(FName("Action.Down.Damaged.Knockdown"), instance.ActionHitTransit.Down);

    instance.AddActionTag(FName("Action.Stand.Damaged.Hit"), instance.ActionDamage.Hit.Stand);
    instance.AddActionTag(FName("Action.Stand.Damaged.Knockback"), instance.ActionDamage.Knockback.Stand);
    instance.AddActionTag(FName("Action.Stand.Damaged.Stun"), instance.ActionDamage.Stun.Stand);

    instance.AddActionTag(FName("Action.Down.Damaged.Hit"), instance.ActionDamage.Hit.Down);
    instance.AddActionTag(FName("Action.Down.Damaged.Knockback"), instance.ActionDamage.Knockback.Down);
    instance.AddActionTag(FName("Action.Down.Damaged.Stun"), instance.ActionDamage.Stun.Down);

    instance.AddActionTag(FName("Action.Down.Normal.KeepDown"), instance.ActionKeepDown);


    

    instance.AddActionTag(FName("Action.Stand.Damaged.Dead"), instance.ActionDead.Stand);
    instance.AddActionTag(FName("Action.Down.Damaged.Dead"), instance.ActionDead.Down);

    instance.TupleArray.Reset();


    instance.AddOtherTag(FName("Player.EquipState.Sword"), instance.PlayerControlSetTag);
    instance.AddOtherTag(FName("AI.EquipState.Sword"), instance.AIControlSetTag);

    instance.AddOtherTag(FName("Character.Monster"), instance.MonsterTag);
    instance.AddOtherTag(FName("Character.Player"), instance.PlayerTag);

}

void FHyGameplayTags::AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
    FHyGameplayTags& instance = FHyGameplayTags::Get();

    InActionTagInst = FGameplayTag::RequestGameplayTag(InTagName);

    for (FGameplayTuple* TagTuple : TupleArray)
    {
        if (TagTuple)
        {
            if (IsWeakTagMatch(InActionTagInst, TagTuple->Tag))
            {
                TagTuple->Container.AddTag(InActionTagInst);
            }
        }
    }
}

void FHyGameplayTags::AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
    FHyGameplayTags& instance = FHyGameplayTags::Get();
    InActionTagInst = FGameplayTag::RequestGameplayTag(InTagName);
}

void FHyGameplayTags::AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple)
{
    FHyGameplayTags& instance = FHyGameplayTags::Get();

    InTagTuple.Tag = FGameplayTag::RequestGameplayTag(InTagName);

    TupleArray.Add(&InTagTuple);
}

int32 FHyGameplayTags::GetActionTagID(const FGameplayTag& InActionTag)
{
    FHyGameplayTags& instance = FHyGameplayTags::Get();

    if (instance.ActionTagIDMap.Contains(InActionTag))
    {
        return instance.ActionTagIDMap[InActionTag];
    }

    ERR_V("Invalid Action Tag %s", *InActionTag.ToString());
    return 0;
}

FGameplayTag FHyGameplayTags::GetDefaultAction(const FGameplayTag& InActionTag)
{
    // TODO 상황에 따라 Idle or DownKeep 으로 나눠 반환

    if (IsDownAction(InActionTag))
    {
        return ActionKeepDown;
    }
    else
    {
        return ActionIdle;
    }
}

FGameplayTag FHyGameplayTags::GetDefaultHit()
{
    return FGameplayTag::RequestGameplayTag(FName("Damaged.Hit"));
}

FGameplayTag FHyGameplayTags::GetDefaultAction()
{
    return FGameplayTag::RequestGameplayTag(FName("Action.Stand.Normal.Idle"));
}

FGameplayTag FHyGameplayTags::GetDefaultCollider()
{
    return FGameplayTag::RequestGameplayTag(FName("AttackCollider.Default"));
}

FName FHyGameplayTags::GetLastNameFromGameplayTag(const FGameplayTag& InTag)
{
    FString TagString = InTag.ToString();
    FString LastPart;

    // 마지막 태그를 Name으로 반환
    if (TagString.Split(TEXT("."), nullptr, &LastPart, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
    {
        return FName(*LastPart);
    }

    return FName(*TagString);
}

FName FHyGameplayTags::ConvertGameplayTagToName(const FGameplayTag& InTag)
{
    // Tag to FName, .빼고 합쳐서

    FString TagString = InTag.ToString();
    TagString.ReplaceInline(TEXT("."), TEXT(""), ESearchCase::IgnoreCase);
    return FName(*TagString);
}


bool FHyGameplayTags::IsDeadAction(const FGameplayTag& InActionTag)
{
    // Dead 액션인가?
    bool bRes = InActionTag.MatchesAnyExact(DeadTuple.Container);
    return bRes;
}

bool FHyGameplayTags::IsDamagedAction(const FGameplayTag& InActionTag)
{
    // Damaged 상태의 액션인가?
    bool bRes = InActionTag.MatchesAnyExact(DamagedParentTuple.Container);
    return bRes;
}

bool FHyGameplayTags::IsMoveAction(const FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionWalk) || InActionTag.MatchesTag(ActionRun))
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsMoveWalk(const FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionWalk))
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsMoveRun(const FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionRun))
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsDashAction(const FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionDash))
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsAttackAction(const FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(AttackTuple.Tag))
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsSkillAction(const FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(SkillTuple.Tag))
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsEvadeAction(const FGameplayTag& InActionTag)
{
    if (InActionTag == ActionEvade)
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsNormalAction(const FGameplayTag& InActionTag, bool bIncludeKeepDown)
{
    if (InActionTag.MatchesTag(NormalTuple.Tag))
    {
        if (bIncludeKeepDown && IsDownAction(InActionTag))
        {
            return false;
        }

        return true;
    }

    return false;
}

bool FHyGameplayTags::CompareDamagedAndHit(const FGameplayTag& InHitTag, const FGameplayTag& InCurAction)
{
    // 현재 Damaged 상태와 Hit를 비교
    // 현재 Damaged 상태보다 더 강한 Hit인 경우에만 true 반환

    EHitStrength HitStrength = GetHitStrength(InHitTag);
    EHitStrength CurStrength = GetHitStrength(InCurAction);
    
    if (HitStrength == EHitStrength::EHitStrength_None || CurStrength == EHitStrength::EHitStrength_None)
    {
        ERR_V("Strenth is invalid");
        return false;
    }

    //LOG_V("Damage Compare NewHit %d  CurDamaged %d", (int32)HitStrength, (int32)CurStrength);
    if (HitStrength > CurStrength)
    {
        return true;
    }

    return false;
}

bool FHyGameplayTags::IsCanChangeHitAction(const FGameplayTag& InHitTag, const FGameplayTag& InCurAction, FGameplayTag& OutAction, FGameplayTag& OutChangeStoreTag, EActionPriority& OutStorePriority)
{
    // Hit 상태로 전환 가능한지 체크

    // 죽은 상태는 false
    if (IsDeadAction(InCurAction))
    {
        return false;
    }

    OutChangeStoreTag = GetDefaultAction(InCurAction);
    OutStorePriority = EActionPriority::ENone;

    if (IsStandAction(InCurAction)) // Stand
    {
        // 일어나는중 예외처리
        if (InCurAction.MatchesTag(ActionHitTransit.Stand))
        {
            return false;
        }



        if (IsDamagedAction(InCurAction))
        {
            // 여기서는 현재 Damaged 상태보다 강한 공격인 경우에만 처리
            // Hit < Knockback < Stun < Knockdonw
            if (CompareDamagedAndHit(InHitTag, InCurAction))
            {
                OutAction = GetDamagedAction(InHitTag);

                // KnockDown으로 변경되는 경우 StoreTag Down으로 예외처리
                if (OutAction.MatchesTag(ActionHitTransit.Down))
                {
                    OutChangeStoreTag = ActionKeepDown;
                    OutStorePriority = EActionPriority::EMedium;
                }
                return true;
            }

            return false;
        }
    }
    else
    {
        OutChangeStoreTag = ActionKeepDown;
        OutStorePriority = EActionPriority::EMedium;

        // 이미 Donw 되어있는 상태
        // KeepDown 상태인 경우에만 Down Hit 동작하도록
        if (InCurAction.MatchesTag(ActionKeepDown))
        {
            OutAction = ActionDamage.Hit.Down;
            return true;
        }

        return false;
    }

    // 그 외에는 허용
    OutAction = GetDamagedAction(InHitTag);

    // KnockDown으로 변경되는 경우 StoreTag Down으로 예외처리
    if (OutAction.MatchesTag(ActionHitTransit.Down))
    {
        OutChangeStoreTag = ActionKeepDown;
    }
    return true;
}
bool FHyGameplayTags::IsDamageTag(const FGameplayTag& InHitTag)
{
    if (InHitTag.MatchesTag(DamagedTuple.Hit.Tag) ||
        InHitTag.MatchesTag(DamagedTuple.Knockback.Tag) ||
        InHitTag.MatchesTag(DamagedTuple.Knockdown.Tag) ||
        InHitTag.MatchesTag(DamagedTuple.Stun.Tag))
    {
        return true;
    }

    return false;
}
EHitStrength FHyGameplayTags::GetHitStrength(const FGameplayTag& InTag)
{
    // 공격 강도 비교를 위해 tag를 enum값으로 변환
    // InTag에는 Action or Hit Tag가 올 수 있음

    if (InTag.MatchesTag(DamagedTuple.Hit.Tag) || InTag.MatchesAny(DamagedTuple.Hit.Container))
    {
        return EHitStrength::EHitStrength_Hit;
    }
    else if (InTag.MatchesTag(DamagedTuple.Knockback.Tag) || InTag.MatchesAny(DamagedTuple.Knockback.Container))
    {
        return EHitStrength::EHitStrength_Knockback;
    }
    else if (InTag.MatchesTag(DamagedTuple.Stun.Tag) || InTag.MatchesAny(DamagedTuple.Stun.Container))
    {
        return EHitStrength::EHitStrength_Stun;
    }
    else if (InTag.MatchesTag(DamagedTuple.Knockdown.Tag) || InTag.MatchesAny(DamagedTuple.Knockdown.Container))
    {
        return EHitStrength::EHitStrength_Knockdown;
    }

    ERR_V("Invalid Hit Info %s", *InTag.ToString());
    return EHitStrength::EHitStrength_Hit;
}
FGameplayTag FHyGameplayTags::GetDamagedAction(const FGameplayTag& InHitTag)
{
    // HitTag에 일치하는 Damaged 상태를 반환함
    if (InHitTag.MatchesTag(DamagedTuple.Hit.Tag))
    {
        return ActionDamage.Hit.Stand;
    }
    else if (InHitTag.MatchesTag(DamagedTuple.Knockback.Tag))
    {
        return ActionDamage.Knockback.Stand;
    }
    else if (InHitTag.MatchesTag(DamagedTuple.Stun.Tag))
    {
        return ActionDamage.Stun.Stand;
    }
    else if (InHitTag.MatchesTag(DamagedTuple.Knockdown.Tag))
    {
        return ActionHitTransit.Down;
    }

    ERR_V("Invalid HitTag %s", *InHitTag.ToString());
    return FGameplayTag::EmptyTag;
}
bool FHyGameplayTags::IsWeakTagMatch(const FGameplayTag& FullTag, const FGameplayTag& IncludeTag)
{
    // A.B.C.D == A.B.C 는 Match함수가 제공하지만
    // A.B.C.D == C.D or A.B.C.D == C 기능은 없으므로 아래와 같이 직접 만듦

    FString FullTagString = FullTag.ToString();
    FString IncludeString = IncludeTag.ToString();

    TArray<FString> FullTagArray;
    TArray<FString> IncludeTagArray;

    FullTagString.ParseIntoArray(FullTagArray, TEXT("."), true);
    IncludeString.ParseIntoArray(IncludeTagArray, TEXT("."), true);

    int32 FullSize = FullTagArray.Num();
    int32 IncludeSize = IncludeTagArray.Num();
    if (FullSize >= IncludeSize)
    {
        for (int32 i = 0; i <= FullSize - IncludeSize; ++i)
        {
            bool bMatch = true;
            for (int32 j = 0; j < IncludeSize; ++j)
            {
                if (FullTagArray[i + j] != IncludeTagArray[j])
                {
                    bMatch = false;
                    break;
                }
            }
            if (bMatch)
            {
                return true;
            }
        }
    }

    return false;

}
bool FHyGameplayTags::IsStandAction(const FGameplayTag& InActionTag)
{
    return InActionTag.MatchesAnyExact(StandTuple.Stand.Container);
}
bool FHyGameplayTags::IsDownAction(const FGameplayTag& InActionTag)
{
    return InActionTag.MatchesAnyExact(StandTuple.Down.Container);
}

