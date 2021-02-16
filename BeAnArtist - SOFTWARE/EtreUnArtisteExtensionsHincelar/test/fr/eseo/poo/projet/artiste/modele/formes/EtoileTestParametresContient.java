package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;

@RunWith(Parameterized.class)
public class EtoileTestParametresContient {
	
	private Coordonnees coordContient; 
	private boolean contient; 
	private int nombreBranches; 
	private double anglePremiereBranche; 
	private double longueurBranche; 
	private double taille;
	
	public EtoileTestParametresContient(double taille, int nombreBranches, double longueurBranche, double anglePremiereBranche,	
			Coordonnees coordContient, boolean contient) {
		this.taille = taille; 
		this.nombreBranches = nombreBranches; 
		this.longueurBranche = longueurBranche; 
		this.anglePremiereBranche = anglePremiereBranche;
		this.coordContient = coordContient;
		this.contient = contient; 
		}
	
	@Parameters(name= "dataEtoile[{index}] : {0}, {1}, {2}, {3}, {4}, {5}") 
	public static Collection<Object[]>dataEtoile(){
		Object[][] dataEtoile = new Object[][] {
			{5, 3, 0, 0.7, new Coordonnees(2.5, 2.5), true},
			{5, 3, 0, 0.7, new Coordonnees(1.7, 1), true},
			

			
		};
		return Arrays.asList(dataEtoile);}	
	
	@Test
	public void testContient() {
		EtoileTestParametresContient etoileTest = new EtoileTestParametresContient(taille, nombreBranches,anglePremiereBranche, 
				longueurBranche, coordContient, contient);
		
		Etoile etoile = new Etoile(new Coordonnees(), etoileTest.taille, etoileTest.nombreBranches, etoileTest.anglePremiereBranche,
				etoileTest.longueurBranche);
		
		assertEquals("Le point est bien contenu dans l'étoile", contient, etoile.contient(coordContient));
	}

}
