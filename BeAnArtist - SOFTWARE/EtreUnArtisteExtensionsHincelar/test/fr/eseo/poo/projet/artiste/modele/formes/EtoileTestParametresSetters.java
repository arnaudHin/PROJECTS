package fr.eseo.poo.projet.artiste.modele.formes;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;


@RunWith(Parameterized.class)
public class EtoileTestParametresSetters {
	private int nombreBranches;
	private double longueurBranches;
	private double anglePremiereBranche;
	private double largeur;
	private double hauteur;
	
	public EtoileTestParametresSetters(double largeur, double hauteur, int nombreBranches, 
			double longueurBranches, double anglePremiereBranche) {
		this.largeur = largeur;
		this.hauteur = hauteur;
		this.nombreBranches = nombreBranches;
		this.longueurBranches = longueurBranches;
		this.anglePremiereBranche = anglePremiereBranche;
	}
	
	@Parameters(name= "dataEtoile[{index}] : {0}, {1}, {2}, {3}, {4}") 
	public static Collection<Object[]>dataEtoile(){
		Object[][] dataEtoile = new Object[][] {
			{-3, -1, 18, 1.1, 4 },
			{-0.1, -0.1, 2, -0.1, -3.15 },
			{-89551122, -80, -90, 1.01, 3.15 },
			{-3, -1, 3200, 1.1, 4 },
			{-3, -1, 2, 1.01, 4 },
			{-0.001, -0.0001, 0, 1.01, 3.149999 }

		};
		return Arrays.asList(dataEtoile);}
	
	@Rule
	public ExpectedException exception = ExpectedException.none();	
	@Test
	public void testNegativesLargeur() {
		EtoileTestParametresSetters testSetters = new EtoileTestParametresSetters(this.largeur, this.hauteur, 
				this.nombreBranches, this.longueurBranches, this.anglePremiereBranche);
        exception.expect(IllegalArgumentException.class);
		Etoile etoile = new Etoile();
		etoile.setLargeur(testSetters.largeur);
	}
	@Test
	public void testNegativesHauteur() {
		EtoileTestParametresSetters testSetters = new EtoileTestParametresSetters(this.largeur, this.hauteur, 
				this.nombreBranches, this.longueurBranches, this.anglePremiereBranche);
        exception.expect(IllegalArgumentException.class);
		Etoile etoile = new Etoile();
		etoile.setHauteur(testSetters.hauteur);
	}			
	
	@Test
	public void testNegatifNbBranches() {
		EtoileTestParametresSetters testSetters = new EtoileTestParametresSetters(this.largeur, this.hauteur, 
				this.nombreBranches, this.longueurBranches, this.anglePremiereBranche);
        exception.expect(IllegalArgumentException.class);
		Etoile etoile = new Etoile();
		etoile.setNombreBranches(testSetters.nombreBranches);
	}	

	@Test
	public void testNegativeLongueurBranches() {
		EtoileTestParametresSetters testSetters = new EtoileTestParametresSetters(this.largeur, this.hauteur, 
				this.nombreBranches, this.longueurBranches, this.anglePremiereBranche);
        exception.expect(IllegalArgumentException.class);
		Etoile etoile = new Etoile();
		etoile.setLongueurBranche(testSetters.longueurBranches);
	}
	
	@Test
	public void testNegatifAngle() {
		EtoileTestParametresSetters testSetters = new EtoileTestParametresSetters(this.largeur, this.hauteur, 
				this.nombreBranches, this.longueurBranches, this.anglePremiereBranche);
        exception.expect(IllegalArgumentException.class);
		Etoile etoile = new Etoile();
		etoile.setAnglePremiereBranche(testSetters.anglePremiereBranche);
	}	
	
	
	

}
