// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/HoloPlayCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Game/HoloPlayCapture.h"

AHoloPlayCharacter::AHoloPlayCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const auto CapsuleComp = GetCapsuleComponent();
	if (nullptr != CapsuleComp)
	{
		SpringArmComp = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArmComp"));
		if (nullptr != SpringArmComp)
		{
			SpringArmComp->SetupAttachment(CapsuleComp);
			SpringArmComp->bUsePawnControlRotation = true;
			SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 100.0f, 50.0f), FRotator(-20.0f, 0.0f, 0.0f));

			CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
			if (nullptr != CameraComp)
			{
				CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
				CameraComp->bUsePawnControlRotation = false;
			}
		}

		CapsuleComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		CapsuleComp->bLightAttachmentsAsGroup = true;
	}

	const auto SkelMeshComp = GetMesh();
	if (nullptr != SkelMeshComp)
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
		if (SkeletalMesh.Succeeded())
		{
			SkelMeshComp->SetSkeletalMesh(SkeletalMesh.Object);
		}
		SkelMeshComp->SetRelativeLocationAndRotation(FVector::UpVector * -90.0f, FRotator(0.0f, -90.0f, 0.0f));

		SkelMeshComp->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

		SkelMeshComp->bReceivesDecals = false;

		SkelMeshComp->SetCollisionObjectType(ECC_Pawn);
		SkelMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SkelMeshComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

		static ConstructorHelpers::FObjectFinder<UClass> AnimBPClass(TEXT("Class'/Game/AnimStarterPack/UE4ASP_HeroTPP_AnimBlueprint.UE4ASP_HeroTPP_AnimBlueprint_C'"));
		if (AnimBPClass.Succeeded())
		{
			SkelMeshComp->SetAnimInstanceClass(AnimBPClass.Object);
		}
	}

	const auto MovementComp = GetCharacterMovement();
	if (nullptr != MovementComp)
	{
		MovementComp->bCrouchMaintainsBaseLocation = true;
		MovementComp->bMaintainHorizontalGroundVelocity = false;

		MovementComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void AHoloPlayCharacter::BeginPlay()
{
	Super::BeginPlay();

	//!< シーンにある AHoloPlayCapture アクタを探す、アクタは予めシーンに置いておくこと (Finding AHoloPlayCapture actor in the scene, AHoloPlayCapture actor must be placed in advance)
	if (nullptr == HoloPlayCapture) 
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHoloPlayCapture::StaticClass(), Actors);
		if (0 < Actors.Num()) 
		{
			HoloPlayCapture = Cast<AHoloPlayCapture>(Actors[0]);
		}
	}
}
void AHoloPlayCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//!< カメラのトランスフォームを AHoloPlayCapture トランスフォームへ適用する (Apply camera's transform to AHoloPlayCapture's transform)
	if (nullptr != HoloPlayCapture)
	{
		HoloPlayCapture->SetActorTransform(CameraComp->GetComponentTransform());
	}
}

void AHoloPlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (nullptr != PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AHoloPlayCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AHoloPlayCharacter::MoveRight);
		PlayerInputComponent->BindAxis("Turn", this, &AHoloPlayCharacter::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &AHoloPlayCharacter::AddControllerPitchInput);
	}
}

