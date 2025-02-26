// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComboAttackComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UComboAttackComponent : public UActorComponent
{
	GENERATED_BODY()

//Methods
public:	
	// Sets default values for this component's properties
	UComboAttackComponent();

	UFUNCTION(BlueprintCallable)
		virtual void LightAttack();

	UFUNCTION(BlueprintCallable)
		virtual void HeavyAttack();

	//Blueprint native function for handling the animation montage and notifies
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PlayAnimationMontage(FName Section, float Speed);

	UFUNCTION(BlueprintCallable)
		void ToggleComboFrame(bool IsWithinComboFrames);

	UFUNCTION(BlueprintCallable)
		void FinishAttack();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartAttack(FName Section, float Speed);

	void SetSkeletalMeshes(USkeletalMeshComponent* FPSkeleton, USkeletalMeshComponent* TPSkeleton);

	void SetAttackMontage(UAnimMontage* Montage);

//Members

public:

	UPROPERTY(BlueprintReadOnly)
	FName AttackSection;

	UPROPERTY(BlueprintReadWrite)
		bool bIsAttacking = false;

	UPROPERTY(BlueprintReadWrite)
		bool bCanAttack = true;

	UPROPERTY(EditAnywhere)
		float ComboDelay = 0.2f;



//Methods
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bComboIsValid();

	uint32 GetSectionAsInt(FName Section);

	void Reset();

//Members
protected:

	UPROPERTY(BlueprintReadOnly)
		USkeletalMeshComponent* FirstPersonSkeleton;

	UPROPERTY(BlueprintReadOnly)
		USkeletalMeshComponent* ThirdPersonSkeleton;

	UPROPERTY(BlueprintReadOnly)
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere)
		float StartingAttackSpeed = 1;

	float AttackSpeed = 1;
	bool bWithinComboFrames = false;
	bool bPlayNextAttack = false;
	int32 ComboCounter = 1;
};
