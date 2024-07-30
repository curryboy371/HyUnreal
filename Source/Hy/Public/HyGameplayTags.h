// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Action/HyActionTypes.h"
#include "HyGameplayTags.generated.h"

/**
 * 
 */

typedef FHyGameplayTags FHyTags;


UENUM(BlueprintType)
enum class EHitStrength : uint8
{
    EHitStrength_None                UMETA(DisplayName = "EHitStrength_None"),
    EHitStrength_Hit                 UMETA(DisplayName = "EHitStrength_Hit"),
    EHitStrength_Knockback           UMETA(DisplayName = "EHitStrength_Knockback"),
    EHitStrength_Stun                UMETA(DisplayName = "EHitStrength_Stun"),
    EHitStrength_Knockdown           UMETA(DisplayName = "EHitStrength_Knockdown"),
};

struct FDetailActionGameplayTag
{
    FGameplayTag Down;
    FGameplayTag Stand;
};

struct FDetailDamagedTag
{
    FDetailActionGameplayTag Hit;
    FDetailActionGameplayTag Knockback;
    FDetailActionGameplayTag Knockdown;
    FDetailActionGameplayTag Stun;
};

struct FGameplayTuple
{
    FGameplayTag Tag;
    FGameplayTagContainer Container;
};

struct FDetailActionTagContainer
{
    FGameplayTuple Down;
    FGameplayTuple Stand;
};

struct FDetailDamagedTagCon
{
    FGameplayTuple Hit;
    FGameplayTuple Knockback;
    FGameplayTuple Knockdown;
    FGameplayTuple Stun;
};




USTRUCT(BlueprintType)
struct FHyGameplayTags
{
	GENERATED_BODY()
public:
    static FHyGameplayTags& Get()
    {
        static FHyGameplayTags Instance;
        return Instance;
    }

    static void InitializeTags();
    void AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst);
    void AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst);

    void AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple);

    int32 GetActionTagID(const FGameplayTag& InActionTag);

    FGameplayTag GetDefaultAction(const FGameplayTag& InActionTag);

    // 생성자에서 디폴트값으로 사용하기 위함
    static FGameplayTag GetDefaultHit();
    static FGameplayTag GetDefaultAction();

    static FGameplayTag GetDefaultCollider();



    FName GetLastNameFromGameplayTag(const FGameplayTag& InTag);
    FName ConvertGameplayTagToName(const FGameplayTag& InTag);



    bool IsCanChangeHitAction(const FGameplayTag& InHitTag, const FGameplayTag& InCurAction, FGameplayTag& OutAction, FGameplayTag& OutChangeStoreTag, EActionPriority& OutStorePriority);

    bool IsDamageTag(const FGameplayTag& InHitTag);
public:
    bool IsStandAction(const FGameplayTag& InActionTag);
    bool IsDownAction(const FGameplayTag& InActionTag);
    bool IsDeadAction(const FGameplayTag& InActionTag);
    bool IsDamagedAction(const FGameplayTag& InActionTag);
    bool IsMoveAction(const FGameplayTag& InActionTag);
    bool IsMoveWalk(const FGameplayTag& InActionTag);
    bool IsMoveRun(const FGameplayTag& InActionTag);

    bool IsDashAction(const FGameplayTag& InActionTag);

    bool IsAttackAction(const FGameplayTag& InActionTag);

    bool IsSkillAction(const FGameplayTag& InActionTag);
    bool IsEvadeAction(const FGameplayTag& InActionTag);

    bool IsNormalAction(const FGameplayTag& InActionTag, bool bIncludeKeepDown = false);


protected:
    bool CompareDamagedAndHit(const FGameplayTag& InHitTag, const FGameplayTag& InCurAction);

    EHitStrength GetHitStrength(const FGameplayTag& InTag);
    FGameplayTag GetDamagedAction(const FGameplayTag& InHitTag);



    bool IsWeakTagMatch(const FGameplayTag& FullTag, const FGameplayTag& IncludeTag);
public:

    FGameplayTag ActionWalk;
    FGameplayTag ActionRun;
    FGameplayTag ActionKeepDown;
    FGameplayTag ActionIdle;
    FGameplayTag ActionSpawn;
    FGameplayTag ActionAttack;
    FGameplayTag ActionAttackDash;


    // Hit Action - Detail ( Stand, Down )
    FDetailActionGameplayTag ActionHitTransit; // make stand or down action
    FDetailActionGameplayTag ActionDead;
    FDetailDamagedTag ActionDamage;

    FGameplayTag ActionDash;
    FGameplayTag ActionEvade;
    FGameplayTag ActionSkill;
    FGameplayTag ActionTest;


    FGameplayTag PlayerControlSetTag;
    FGameplayTag AIControlSetTag;

    FGameplayTag MonsterTag;
    FGameplayTag PlayerTag;


public:
    // 컨테이너
    FGameplayTuple NormalTuple; // Normal
    FGameplayTuple SkillTuple; // Skill
    FGameplayTuple AttackTuple; // Attack

    FGameplayTuple DeadTuple; // Dead
    FGameplayTuple DamagedParentTuple; // Damaged

    FDetailActionTagContainer StandTuple; // Stand Down

    FDetailDamagedTagCon DamagedTuple; // Hit  Knockback Stun KnockDown

    TArray<FGameplayTuple*>  TupleArray;

protected:
    // 비교용 태그

protected:


    TMap<FGameplayTag, int32> ActionTagIDMap; // tag를 id화 하여 저장해두는 맵
    int32 TagID;
};
